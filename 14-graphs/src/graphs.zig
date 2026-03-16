const std = @import("std");

const List = std.ArrayList;
const MultiList = std.MultiArrayList;

const Allocator = std.mem.Allocator;
const Deque = std.Deque;
const StringHashMap = std.StringHashMap;

pub fn Graph(comptime W: type, comptime isDirected: bool) type {
    return struct {
        const Self = @This();
        pub const Error = error{ NodeExists, IsDirected, IsNotDirected };
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

            var dist: []usize = try self.allocator.alloc(usize, self.vertices.items.len);
            defer self.allocator.free(dist);
            @memset(dist, std.math.maxInt(usize));

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
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
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
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
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
            var visited: []u8 = try self.allocator.alloc(u8, self.vertices.items.len);
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
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
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
        // In topological sorting, node u will always appear before node v if there is a directed edge from node u towards node v(u -> v).
        // The Output will be True if your topological sort is correct otherwise it will be False.
        pub fn TopologicalSortDfs(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), *Node) anyerror!void,
        ) !void {
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
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

        pub fn ShortestPathInDAG(self: *Self, ctx: anytype, visit: fn (@TypeOf(ctx), *Node, usize) anyerror!void) !void {
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
            @memset(gen.distance, std.math.maxInt(usize));
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
    };
}
