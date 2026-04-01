const std = @import("std");
const Allocator = std.mem.Allocator;

const Order = std.math.Order;
const List = std.ArrayList;
const Deque = std.Deque;
const StringHashMap = std.StringHashMap;
const PriorityQueue = std.PriorityQueue;
const assert = std.debug.assert;
pub fn Graph(comptime W: type, comptime isDirected: bool) type {
    return struct {
        const Self = @This();
        pub const Error = error{ NodeExists, IsDirected, IsNotDirected, NegativeCycle };
        pub const Node = struct {
            index: ?usize,
        };
        const Edge = struct {
            weight: W,
            destination: *Node,
        };
        const VerexType = List(*Node);
        const AdjType = List(List(Edge));

        vertices: VerexType,
        adj: AdjType,
        allocator: Allocator,
        is_directed: bool = isDirected,

        pub fn init(allocator: Allocator) !Self {
            return .{
                .allocator = allocator,
                .vertices = try .initCapacity(allocator, 0),
                .adj = try .initCapacity(allocator, 0),
            };
        }

        pub fn initDirected(allocator: Allocator, is_directed: bool) !Self {
            return .{
                .allocator = allocator,
                .vertices = try .initCapacity(allocator, 0),
                .adj = try .initCapacity(allocator, 0),
                .is_directed = is_directed,
            };
        }

        pub fn deinit(self: *Self) void {
            self.vertices.deinit(self.allocator);
            for (0..self.adj.items.len) |i|
                self.adj.items[i].deinit(self.allocator);
            self.adj.deinit(self.allocator);
        }

        fn verticesCount(self: *Self) usize {
            return self.vertices.items.len;
        }

        pub fn insert(self: *Self, node: *Node) !void {
            // if (node.index) |_| return Error.NodeExists;
            if (node.index) |_| return;
            try self.vertices.append(self.allocator, node);
            const edge_list = try List(Edge).initCapacity(self.allocator, 0);
            try self.adj.append(self.allocator, edge_list);
            node.index = self.vertices.items.len - 1;
        }

        pub fn contains(self: *Self, node: *Node) bool {
            if (node.index == null) return false;
            if (node.index.? >= self.vertices.items.len) return false;
            const index = node.index.?;
            if (self.vertices.items[index] == node) return true;
            return false;
        }
        fn reversedEgdeGraph(self: *Self, graph: *Self) !void {
            for (self.vertices.items) |node| {
                try graph.vertices.append(self.allocator, node);
                const edge_list = try List(Edge).initCapacity(self.allocator, 0);
                try graph.adj.append(self.allocator, edge_list);
            }
            for (0..self.adj.items.len) |i| {
                for (self.adj.items[i].items) |edge| {
                    const dest_index = edge.destination.index.?;
                    try graph.adj.items[dest_index].append(self.allocator, .{
                        .destination = self.vertices.items[i],
                        .weight = edge.weight,
                    });
                }
            }
        }

        /// create a edge from source to destination
        /// if isDirected is true create an edge from destination and source
        pub fn addEdge(
            self: *Self,
            source: *Node,
            destination: *Node,
            weight: W,
        ) !void {
            if (source.index == null or destination.index == null) return;
            const no_vertices = self.vertices.items.len;
            if (source.index.? > no_vertices or destination.index.? > no_vertices) return;

            const source_index = source.index.?;
            // add the edge in adjacent list from source to destination
            try self.adj.items[source_index].append(self.allocator, .{
                .destination = destination,
                .weight = weight,
            });

            // add an edge in adjacent list from destination to source
            if (!self.is_directed) {
                const dest_index = destination.index.?;
                try self.adj.items[dest_index].append(self.allocator, .{
                    .destination = source,
                    .weight = weight,
                });
            }
        }

        pub fn BfsTraversal(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
        ) !void {
            if (self.vertices.items.len == 0) return;
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);

            var queue = try Deque(*Node).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);

            try queue.pushBack(self.allocator, self.vertices.items[0]);

            while (queue.len > 0) {
                const node = queue.popFront();
                if (node) |n| {
                    const node_index = n.index.?;

                    for (self.adj.items[node_index].items) |edge| {
                        const index = edge.destination.index.?;
                        if (!visited[index]) {
                            try queue.pushBack(self.allocator, edge.destination);
                            visited[index] = true;
                        }
                    }
                    visited[node_index] = true;
                    try visit(ctx, n);
                }
            }
        }

        pub fn DfsTraversal(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
        ) !void {
            const visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);
            for (self.vertices.items) |vertex| {
                const vertex_index = vertex.index.?;
                if (!visited[vertex_index]) {
                    visited[vertex_index] = true;
                    try self.Dfs(self.vertices.items[vertex_index], ctx, visit, visited);
                }
            }
        }

        fn Dfs(
            self: *Self,
            node: *Node,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
            visited: []bool,
        ) !void {
            try visit(ctx, node);
            const node_index = node.index.?;
            visited[node_index] = true;
            const edges = self.adj.items[node_index];

            // travel all its neighbourers
            for (edges.items) |edge| {
                if (!visited[edge.destination.index.?]) {
                    try self.Dfs(edge.destination, ctx, visit, visited);
                }
            }
        }

        /// Given an Undirected Graph having unit weight,
        /// find the shortest path from the source to all other nodes in this graph.
        /// In this problem statement, we have assumed the source vertex to be ‘0’.
        /// If a vertex is unreachable from the source node, then return -1 for that vertex.
        pub fn shortestPath(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), node: *Node, dist: usize) anyerror!void,
            node: *Node,
        ) !void {
            if (node.index == null) return;
            if (node.index.? > self.vertices.items.len) return;

            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);

            const dist: []usize = try self.allocator.alloc(usize, self.vertices.items.len);
            defer self.allocator.free(dist);
            @memset(dist, std.math.maxInt(W));

            var queue = try Deque(struct {
                node: *Node,
                dist: usize,
            }).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);

            try queue.pushBack(self.allocator, .{
                .node = self.vertices.items[node.index.?],
                .dist = 0,
            });

            while (queue.len > 0) {
                const front = queue.popFront();
                if (front) |n| {
                    const index = n.node.index.?;

                    // traverse all the adjacent nodes
                    for (self.adj.items[index].items) |edge| {
                        const dest_index = edge.destination.index.?;

                        // push to queue if not visited
                        if (!visited[dest_index]) {
                            const distance = n.dist + 1;
                            if (distance < dist[dest_index])
                                try queue.pushBack(self.allocator, .{
                                    .node = edge.destination,
                                    .dist = distance,
                                });
                            visited[dest_index] = true;
                        }
                    }
                    visited[index] = true;
                    try visit(ctx, n.node, n.dist);
                }
            }
        }

        pub fn NumberOfProvinces(self: *Self) !usize {
            const visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);
            const gen = struct {
                fn visit(_: void, _: *Node) !void {}
            };
            var count: usize = 0;
            for (0..self.vertices.items.len) |i| {
                if (!visited[i]) {
                    count += 1;
                    try self.Dfs(self.vertices.items[i], {}, gen.visit, visited);
                }
            }
            return count;
        }

        /// Problem Statement: Given an undirected graph with V vertices and E edges, check whether it contains any cycle or not.
        /// using BFS
        pub fn DetectCycleUndirected(self: *Self) !bool {
            if (self.is_directed) return Error.IsDirected;
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);

            var queue = try Deque(struct { curr: *Node, prev: *Node }).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);

            for (self.vertices.items) |vertex| {
                const vertex_index = vertex.index.?;
                if (!visited[vertex_index]) {
                    visited[vertex_index] = true;
                    try queue.pushBack(
                        self.allocator,
                        .{ .curr = vertex, .prev = vertex },
                    );
                }
                while (queue.len > 0) {
                    const front = queue.popFront();
                    if (front) |n| {
                        const current_index = n.curr.index.?;
                        const prev_index = n.prev.index.?;
                        for (self.adj.items[current_index].items) |edge| {
                            const dest_index = edge.destination.index.?;
                            if (!visited[dest_index]) {
                                visited[dest_index] = true;
                                try queue.pushBack(self.allocator, .{ .curr = edge.destination, .prev = n.curr });
                            } else if (dest_index != prev_index) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }

        pub fn DetectCycleUndirectedDfs(self: *Self) !bool {
            if (self.is_directed) return Error.IsDirected;
            const visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);

            for (self.vertices.items) |vertex| {
                const vertex_index = vertex.index.?;
                if (!visited[vertex_index])
                    if (self.DetectCycleDfs(.{ .curr = vertex_index, .prev = vertex_index }, visited))
                        return true;
            }
            return false;
        }

        fn DetectCycleDfs(self: *Self, point: struct { curr: usize, prev: usize }, visited: []bool) bool {
            visited[point.curr] = true;
            for (self.adj.items[point.curr].items) |edge| {
                const dest_index = edge.destination.index.?;
                if (!visited[dest_index]) {
                    if (self.DetectCycleDfs(.{ .curr = edge.destination.index.?, .prev = point.curr }, visited)) return true;
                } else if (dest_index != point.prev)
                    return true;
            }
            return false;
        }

        pub fn IsBipartiteGraph(self: *Self) !bool {
            const visited: []u8 = try self.allocator.alloc(u8, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, 0);
            for (self.vertices.items) |vertex| {
                if (visited[vertex.index.?] == 0) {
                    if (self.bipartiteDFS(0, vertex, visited) == false) return false;
                }
            }
            return true;
        }
        fn bipartiteDFS(self: *Self, color: u8, vertex: *Node, visited: []u8) bool {
            const opp: u8 = if (color == 1) 2 else 1;
            visited[vertex.index.?] = color;
            for (self.adj.items[vertex.index.?].items) |edge| {
                if (visited[edge.destination.index.?] == 0) {
                    if (self.bipartiteDFS(opp, edge.destination, visited) == false) return false;
                } else if (visited[edge.destination.index.?] == color) return false;
            }
            return true;
        }

        pub fn DetectCycleDirectedDfs(self: *Self) !bool {
            const visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);

            const pathVisited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(pathVisited);
            @memset(pathVisited, false);

            for (self.vertices.items) |node| {
                const node_index = node.index.?;
                if (!visited[node_index]) {
                    if (try self.detectCycleDirectedDfs(node, visited, pathVisited)) return true;
                }
            }
            return false;
        }
        fn detectCycleDirectedDfs(
            self: *Self,
            vertex: *Node,
            visited: []bool,
            pathVisited: []bool,
        ) !bool {
            const vertex_index = vertex.index.?;
            visited[vertex_index] = true;
            pathVisited[vertex_index] = true;

            for (self.adj.items[vertex_index].items) |edge| {
                const dest_index = edge.destination.index.?;
                if (!visited[dest_index]) {
                    if (try self.detectCycleDirectedDfs(edge.destination, visited, pathVisited)) return true;
                } else if (pathVisited[dest_index]) return true;
            }

            pathVisited[vertex_index] = false;
            return false;
        }

        /// Problem Statement: Given a Directed Graph with V vertices and E edges,
        /// check whether it contains any cycle or not using BFS.
        /// Kahn's Algorithm
        pub fn DetectCycleDirectedBfs(self: *Self) !bool {
            if (!self.is_directed) return Error.IsNotDirected;
            var indegree: []usize = try self.allocator.alloc(usize, self.vertices.items.len);
            defer self.allocator.free(indegree);
            @memset(indegree, 0);

            var count: usize = 0;

            // determining indegree of every vertices
            for (self.vertices.items) |node| {
                const node_index = node.index.?;
                for (self.adj.items[node_index].items) |edge| {
                    const dest_index = edge.destination.index.?;
                    indegree[dest_index] += 1;
                }
            }

            var queue = try Deque(*Node).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);

            for (self.vertices.items, 0..) |_, i| {
                if (indegree[i] == 0) {
                    try queue.pushBack(self.allocator, self.vertices.items[i]);
                }
            }
            while (queue.len > 0) {
                const front_node = queue.popFront();
                if (front_node) |node| {
                    const node_index = node.index.?;
                    count += 1;
                    for (self.adj.items[node_index].items) |edge| {
                        const dest_index = edge.destination.index.?;
                        indegree[dest_index] -= 1;
                        if (indegree[dest_index] == 0) try queue.pushBack(self.allocator, edge.destination);
                    }
                }
            }

            if (count == self.vertices.items.len) return false;
            return true;
        }

        /// Problem Statement: Given a Directed Acyclic Graph (DAG) with V vertices labeled from 0 to V-1.
        /// The graph is represented using an adjacency list where adj[i] lists all nodes connected to node.
        /// Find any Topological Sorting of that Graph.
        /// In topological sorting, node u will always appear before node v if there is a directed edge from node u towards node v(u -> v).
        /// The Output will be True if your topological sort is correct otherwise it will be False.
        pub fn TopologicalSortDfs(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
        ) !void {
            const visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);
            @memset(visited, false);

            var stk = try Deque(*Node).initCapacity(self.allocator, 0);
            defer stk.deinit(self.allocator);

            for (self.vertices.items) |node| {
                const node_index = node.index.?;
                if (!visited[node_index]) {
                    try self.topologicalSortDfs(node, visited, &stk);
                }
            }
            while (stk.popBack()) |node| try visit(ctx, node);
        }
        fn topologicalSortDfs(self: *Self, vertex: *Node, visited: []bool, stk: *Deque(*Node)) !void {
            const vertex_index = vertex.index.?;
            visited[vertex_index] = true;
            for (self.adj.items[vertex_index].items) |edge| {
                const dest_index = edge.destination.index.?;
                if (!visited[dest_index]) try self.topologicalSortDfs(edge.destination, visited, stk);
            }
            try stk.pushBack(self.allocator, vertex);
        }

        /// Kahn's algorithm
        pub fn TopologicalSortBfs(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
        ) !void {
            var indegree: []usize = try self.allocator.alloc(usize, self.vertices.items.len);
            defer self.allocator.free(indegree);
            @memset(indegree, 0);

            var toposort = try List(*Node).initCapacity(self.allocator, 0);
            defer toposort.deinit(self.allocator);

            // determining indegree of every vertices
            for (self.vertices.items) |node| {
                const node_index = node.index.?;
                for (self.adj.items[node_index].items) |edge| {
                    const dest_index = edge.destination.index.?;
                    indegree[dest_index] += 1;
                }
            }

            var queue = try Deque(*Node).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);

            for (self.vertices.items, 0..) |_, i| {
                if (indegree[i] == 0) {
                    try queue.pushBack(self.allocator, self.vertices.items[i]);
                }
            }

            while (queue.len > 0) {
                const front_node = queue.popFront();
                if (front_node) |node| {
                    const node_index = node.index.?;
                    try toposort.append(self.allocator, node);

                    for (self.adj.items[node_index].items) |edge| {
                        const dest_index = edge.destination.index.?;
                        indegree[dest_index] -= 1;
                        if (indegree[dest_index] == 0) try queue.pushBack(self.allocator, edge.destination);
                    }
                }
            }
            for (toposort.items) |node| try visit(ctx, node);
        }

        pub fn ShortestPathInDAG(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node, usize) anyerror!void,
        ) !void {
            if (!self.is_directed) return Error.IsNotDirected;
            var topoSortList: Deque(*Node) = try .initCapacity(self.allocator, 0);
            defer topoSortList.deinit(self.allocator);
            const gen = struct {
                const Gen = @This();
                var distance: []usize = undefined;
                var adj_items: []List(Edge) = undefined;
                fn topoVisit(_: void, n: *Node) !void {
                    const current_index = n.index.?;
                    for (Gen.adj_items[current_index].items) |edge| {
                        const dest_index = edge.destination.index.?;
                        if (Gen.distance[current_index] + edge.weight < Gen.distance[dest_index]) {
                            Gen.distance[dest_index] = Gen.distance[current_index] + edge.weight;
                        }
                    }
                }
            };
            gen.adj_items = self.adj.items;
            gen.distance = try self.allocator.alloc(usize, self.vertices.items.len);
            defer self.allocator.free(gen.distance);
            @memset(gen.distance, std.math.maxInt(W));
            gen.distance[self.vertices.items[0].index.?] = 0;

            try self.TopologicalSortBfs({}, gen.topoVisit);
            for (0..gen.distance.len) |i| try visit(ctx, self.vertices.items[i], gen.distance[i]);
        }

        pub fn EventualSafeNodes(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
        ) !void {
            if (!self.is_directed) return Error.IsNotDirected;
            var reversedGraph: Self = try .init(self.allocator);
            defer reversedGraph.deinit();
            try self.reversedEgdeGraph(&reversedGraph);

            var indegree: []usize = try self.allocator.alloc(usize, self.vertices.items.len);
            defer self.allocator.free(indegree);
            @memset(indegree, 0);

            var queue = try Deque(*Node).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);

            for (self.vertices.items, 0..) |node, i| {
                const node_index = node.index.?;
                indegree[node_index] = self.adj.items[node_index].items.len;
                if (indegree[node_index] == 0) {
                    try queue.pushBack(self.allocator, reversedGraph.vertices.items[i]);
                }
            }

            while (queue.len > 0) {
                const front = queue.popFront();
                if (front) |node| {
                    const node_index = node.index.?;
                    try visit(ctx, node);
                    for (reversedGraph.adj.items[node_index].items) |edge| {
                        const dest_index = edge.destination.index.?;
                        indegree[dest_index] -= 1;
                        if (indegree[dest_index] == 0) try queue.pushBack(self.allocator, edge.destination);
                    }
                }
            }
        }

        const DistNode = struct { dist: usize, node: *Node };
        /// Problem Statement: Given a weighted, undirected, and connected graph.
        /// You are given the source vertex S and You have to Find the shortest distance of all the vertex from the source vertex S.
        /// You have to return a list of integers denoting the shortest distance between each node and Source vertex S.
        /// Note: The Graph doesn’t contain any negative weight cycle
        pub fn DijkstraUndirected(
            self: *Self,
            source: *Node,
            dest: *Node,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
        ) !void {
            const Gen = struct {
                fn lessThan(context: void, a: DistNode, b: DistNode) Order {
                    _ = context;
                    return std.math.order(a.dist, b.dist);
                }
            };
            const MinHeap = PriorityQueue(DistNode, void, Gen.lessThan);
            var pq: MinHeap = .empty;
            defer pq.deinit(self.allocator);

            var distance = try self.allocator.alloc(W, self.vertices.items.len);
            defer self.allocator.free(distance);
            @memset(distance, std.math.maxInt(W));
            distance[source.index.?] = 0;
            try pq.push(self.allocator, .{ .node = source, .dist = 0 });

            var parent = try self.allocator.alloc(*Node, self.vertices.items.len);
            defer self.allocator.free(parent);
            for (0..parent.len) |i| parent[i] = self.vertices.items[i];

            while (pq.count() > 0) {
                const front_dist_node = pq.pop();
                if (front_dist_node) |fdn| {
                    const curr_node = fdn.node;
                    const curr_node_index = curr_node.index.?;
                    const curr_node_weight = fdn.dist;

                    for (self.adj.items[curr_node_index].items) |edge| {
                        const dest_index = edge.destination.index.?;
                        if (curr_node_weight + edge.weight < distance[dest_index]) {
                            distance[dest_index] = curr_node_weight + edge.weight;
                            parent[dest_index] = curr_node;
                            try pq.push(self.allocator, .{ .node = edge.destination, .dist = distance[dest_index] });
                        }
                    }
                }
            }
            if (distance[dest.index.?] == std.math.maxInt(W)) return;
            var node_index = dest.index.?;

            var path: Deque(*Node) = try .initCapacity(self.allocator, 0);
            defer path.deinit(self.allocator);
            try path.pushBack(self.allocator, dest);

            while (node_index != parent[node_index].index.?) {
                try path.pushBack(self.allocator, parent[node_index]);
                node_index = parent[node_index].index.?;
            }
            while (path.popBack()) |node| try visit(ctx, node);
        }

        /// You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections.
        /// The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
        /// You are given an integer n and a 2D integer array ‘roads’ where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel.
        /// You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
        /// Return the number of ways you can arrive at your destination in the shortest amount of time.
        pub fn NumberOfWaysToArrive(self: *Self, source: *Node, dest: *Node) !usize {
            const Gen = struct {
                fn lessThan(context: void, a: DistNode, b: DistNode) Order {
                    _ = context;
                    return std.math.order(a.dist, b.dist);
                }
            };

            var distance = try self.allocator.alloc(W, self.vertices.items.len);
            defer self.allocator.free(distance);
            @memset(distance, std.math.maxInt(W));
            distance[source.index.?] = 0;

            var ways = try self.allocator.alloc(usize, self.vertices.items.len);
            defer self.allocator.free(ways);
            @memset(ways, 0);
            ways[source.index.?] = 1;

            const MinHeap = PriorityQueue(DistNode, void, Gen.lessThan);
            var pq: MinHeap = .empty;
            defer pq.deinit(self.allocator);
            try pq.push(self.allocator, .{ .node = source, .dist = 0 });

            while (pq.items.len > 0) {
                const front_dist_node = pq.pop();
                if (front_dist_node) |fdn| {
                    const curr_node = fdn.node;
                    const curr_node_index = curr_node.index.?;
                    const curr_node_weight = fdn.dist;

                    for (self.adj.items[curr_node_index].items) |edge| {
                        const dest_index = edge.destination.index.?;
                        const new_dist = curr_node_weight + edge.weight;
                        if (new_dist < distance[dest_index]) {
                            distance[dest_index] = new_dist;
                            try pq.push(self.allocator, .{ .node = edge.destination, .dist = new_dist });
                            ways[dest_index] = ways[curr_node_index];
                        } else if (new_dist == distance[dest_index]) ways[dest_index] += ways[curr_node_index];
                    }
                }
            }
            return ways[dest.index.?];
        }
        /// Problem Statement: Given a weighted, directed and connected graph of V vertices and E edges, Find the shortest distance of all the vertices from the source vertex S. Note: If the Graph contains a negative cycle then return an array consisting of only -1.
        pub fn Bellmanford(
            self: *Self,
            source: *Node,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node, i64) anyerror!void,
        ) !void {
            assert(self.is_directed);
            var distance = try self.allocator.alloc(W, self.verticesCount());
            defer self.allocator.free(distance);
            @memset(distance, std.math.maxInt(W));
            distance[source.index.?] = 0;

            // relax all the edges for all the edges
            for (0..self.verticesCount()) |_| {
                for (self.vertices.items) |vertex| {
                    const index = vertex.index.?;
                    for (self.adj.items[index].items) |edge| {
                        const u_index = index;
                        const v_index = edge.destination.index.?;
                        const wt = edge.weight;
                        if (distance[u_index] != std.math.maxInt(W) and (distance[u_index] + wt) < distance[v_index]) {
                            distance[v_index] = distance[u_index] + wt;
                        }
                    }
                }
            }
            // check for negative cycles
            for (self.vertices.items) |vertex| {
                const index = vertex.index.?;
                for (self.adj.items[index].items) |edge| {
                    const u_index = index;
                    const v_index = edge.destination.index.?;
                    const wt = edge.weight;
                    if (distance[u_index] != std.math.maxInt(W) and (distance[u_index] + wt) < distance[v_index])
                        return Error.NegativeCycle;
                }
            }

            for (distance, 0..) |dist, i| try visit(ctx, self.vertices.items[i], dist);
        }

        pub fn FloydWarshallAlgorithm(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node, *Node, W) anyerror!void,
        ) !void {
            const adjacenyMatrix = try self.allocator.alloc([]W, self.verticesCount());
            defer self.allocator.free(adjacenyMatrix);
            defer for (0..adjacenyMatrix.len) |i| self.allocator.free(adjacenyMatrix[i]);
            for (adjacenyMatrix, 0..) |*row, i| {
                row.* = try self.allocator.alloc(W, self.verticesCount());
                @memset(row.*, std.math.maxInt(W));
                row.*[i] = 0;
            }
            for (self.vertices.items) |node| {
                const index = node.index.?;
                for (self.adj.items[index].items) |edge| {
                    const dest_index = edge.destination.index.?;
                    adjacenyMatrix[index][dest_index] = edge.weight;
                }
            }

            for (0..self.vertices.items.len) |through| {
                for (0..adjacenyMatrix.len) |i| {
                    for (0..adjacenyMatrix.len) |j| {
                        if (adjacenyMatrix[i][through] == std.math.maxInt(W)) continue;
                        if (adjacenyMatrix[through][j] == std.math.maxInt(W)) continue;
                        const res: W = adjacenyMatrix[i][through] + adjacenyMatrix[through][j];
                        if (res < adjacenyMatrix[i][j]) adjacenyMatrix[i][j] = res;
                    }
                }
            }

            for (0..adjacenyMatrix.len) |i| {
                for (0..adjacenyMatrix.len) |j| {
                    const source = self.vertices.items[i];
                    const destination = self.vertices.items[j];
                    try visit(ctx, source, destination, adjacenyMatrix[i][j]);
                }
            }
            // for (0..adjacenyMatrix.len) |i| {
            //     for (0..adjacenyMatrix.len) |j| {
            //         if (adjacenyMatrix[i][j] == std.math.maxInt(W))
            //             std.debug.print("∞ \t", .{})
            //         else
            //             std.debug.print("{d}\t", .{adjacenyMatrix[i][j]});
            //     }
            //     std.debug.print("\n", .{});
            // }
        }
    };
}
pub const Graphusize = Graph(usize, false);
