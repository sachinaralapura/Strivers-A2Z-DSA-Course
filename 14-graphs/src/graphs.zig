const std = @import("std");

const List = std.ArrayList;
const MultiList = std.MultiArrayList;

const Allocator = std.mem.Allocator;
const Deque = std.Deque;

pub const Point = struct {
    row: i32,
    col: i32,
};

pub fn Graph(comptime W: type, comptime isDirected: bool) type {
    return struct {
        const Self = @This();
        pub const Error = error{ NodeExists, IsDirected };
        pub const Node = struct {
            index: ?usize,
        };
        const Edge = struct {
            weight: W,
            destination: *Node,
        };
        const VerexType = List(*Node);
        const AdjType = List(List(Edge));

        // vertices: List(V),
        // adjacencyList: List(List(Edge)),
        vertices: VerexType,
        adj: AdjType,
        allocator: Allocator,

        pub fn init(allocator: Allocator) !Self {
            return .{
                .allocator = allocator,
                .vertices = try .initCapacity(allocator, 0),
                .adj = try .initCapacity(allocator, 0),
            };
        }

        pub fn deinit(self: *Self) void {
            self.vertices.deinit(self.allocator);
            for (0..self.adj.items.len) |i|
                self.adj.items[i].deinit(self.allocator);
            self.adj.deinit(self.allocator);
        }

        pub fn insert(self: *Self, node: *Node) !void {
            if (node.index) |_| return Error.NodeExists;
            try self.vertices.append(self.allocator, node);
            // node = @constCast(node);
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

        /// create a edge from source to destination
        /// if isDirected is true create an edge from destination and source
        pub fn addEdge(self: *Self, source: *Node, destination: *Node, weight: W) !void {
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
            if (!isDirected) {
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
                        const edge_index = edge.destination.index.?;

                        // push to queue if not visited
                        if (!visited[edge_index]) {
                            const distance = n.dist + 1;
                            if (distance < dist[edge_index])
                                try queue.pushBack(self.allocator, .{
                                    .node = edge.destination,
                                    .dist = distance,
                                });
                            visited[edge_index] = true;
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
        pub fn DetectCycleUndirected(self: *Self) !bool {
            if (isDirected) return Error.IsDirected;
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);

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
                            } else if (prev_index != dest_index) {
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
    };
}

const drow = [_]i32{ -1, 0, 1, 0 };
const dcol = [_]i32{ 0, 1, 0, -1 };

/// Given an n x m grid, where each cell has the following values : 2 - represents a rotten orange , 1 - represents a Fresh orange , 0 - represents an Empty Cell .
/// Every minute, if a fresh orange is adjacent to a rotten orange in 4-direction ( upward, downwards, right, and left ) it becomes rotten.
/// Return the minimum number of minutes required such that none of the cells has a Fresh Orange. If it's not possible, return -1..
pub fn RottenOranges(
    allocator: Allocator,
    matrix: [][]u8,
) !?usize {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    var queue: Deque(struct { row: i32, cols: i32 }) = try .initCapacity(allocator, 0);
    defer queue.deinit(allocator);

    var visited: [][]bool = try allocator.alloc([]bool, matrix.len);
    defer allocator.free(visited);
    defer for (0..visited.len) |i| allocator.free(visited[i]);
    for (visited, 0..) |*row, i| {
        row.* = try allocator.alloc(bool, matrix[i].len);
        @memset(row.*, false);
    }

    // push initial rotten oranges
    for (0..n) |i| {
        for (0..m) |j| {
            if (matrix[i][j] == 2) {
                try queue.pushBack(allocator, .{ .row = @intCast(i), .cols = @intCast(j) });
                visited[i][j] = true;
            }
        }
    }

    var time: usize = 0;

    while (queue.len > 0) : (time += 1) {
        const count = queue.len;
        for (0..count) |_| {
            const orange = queue.popFront();
            if (orange) |index| {
                for (0..4) |i| {
                    const nrow: i32 = @intCast(index.row + drow[i]);
                    const ncol: i32 = @intCast(index.cols + dcol[i]);
                    if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and
                        !visited[@intCast(nrow)][@intCast(ncol)] and
                        matrix[@intCast(nrow)][@intCast(ncol)] == 1)
                    {
                        try queue.pushBack(allocator, .{ .row = @intCast(nrow), .cols = @intCast(ncol) });
                        visited[@intCast(nrow)][@intCast(ncol)] = true;
                    }
                }
            }
        }
    }

    for (0..n) |i|
        for (0..m) |j|
            if (visited[i][j] == false and matrix[i][j] == 1)
                return null;

    return time - 1;
}

/// An image is represented by a 2-D array of integers, each integer representing the pixel value of the image.
/// Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.
pub fn FloodFill(
    alloc: Allocator,
    matrix: [][]u8,
    fillColor: u8,
    initialPoint: Point,
) !void {
    var visited: [][]bool = try alloc.alloc([]bool, matrix.len);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);
    for (visited, 0..) |*row, i| {
        row.* = try alloc.alloc(bool, matrix[i].len);
        @memset(row.*, false);
    }
    floodfillDfs(
        initialPoint,
        matrix,
        visited,
        fillColor,
        matrix[@intCast(initialPoint.row)][@intCast(initialPoint.col)],
    );
}

fn floodfillDfs(
    pt: Point,
    matrix: [][]u8,
    visited: [][]bool,
    fillColor: u8,
    iniColor: u8,
) void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    // fill the color
    matrix[@intCast(pt.row)][@intCast(pt.col)] = fillColor;
    for (0..4) |i| {
        const nrow: i32 = @intCast(pt.row + drow[i]);
        const ncol: i32 = @intCast(pt.col + dcol[i]);
        if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and
            !visited[@intCast(nrow)][@intCast(ncol)] and // if not visited
            matrix[@intCast(nrow)][@intCast(ncol)] == iniColor // if it is same as initial color
        ) {
            visited[@intCast(nrow)][@intCast(ncol)] = true;
            floodfillDfs(.{ .row = nrow, .col = ncol }, matrix, visited, fillColor, iniColor);
        }
    }
}
