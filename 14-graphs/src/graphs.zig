const std = @import("std");

const List = std.ArrayList;
const MultiList = std.MultiArrayList;

const Allocator = std.mem.Allocator;
const Deque = std.Deque;
const StringHashMap = std.StringHashMap;

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
        /// using BFS
        pub fn DetectCycleUndirected(self: *Self) !bool {
            if (self.is_directed) return Error.IsDirected;
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

        pub fn DetectCycleUndirectedDfs(self: *Self) !bool {
            if (self.is_directed) return Error.IsDirected;
            var visited: []bool = try self.allocator.alloc(bool, self.vertices.items.len);
            defer self.allocator.free(visited);

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
    };
}

pub const Point = struct {
    row: i32,
    col: i32,
};
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

/// Given a binary grid of N*M. Find the distance of the nearest 1 in the grid for each cell.
pub fn OneDistance(
    alloc: Allocator,
    matrix: [][]u8,
    result: [][]usize,
) !void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    const DistPoint = struct {
        pt: Point,
        dist: usize,
    };

    // visited
    var visited: [][]bool = try alloc.alloc([]bool, n);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);

    // queue
    var queue = try Deque(DistPoint).initCapacity(alloc, 0);
    defer queue.deinit(alloc);

    for (0..n) |i| {
        // set visited[i]
        visited[i] = try alloc.alloc(bool, matrix[i].len);
        @memset(visited[i], false);

        // set initial visited, queue and result
        for (0..matrix[i].len) |j| {
            result[i][j] = 0;
            if (matrix[i][j] == 1) {
                try queue.pushBack(
                    alloc,
                    .{ .pt = .{ .row = @intCast(i), .col = @intCast(j) }, .dist = 0 },
                );
                visited[i][j] = true;
            } else visited[i][j] = false;
        }
    }

    while (queue.len > 0) {
        const front = queue.popFront();
        if (front) |pt| {
            result[@intCast(pt.pt.row)][@intCast(pt.pt.col)] = pt.dist;
            for (0..4) |i| {
                const nrow = pt.pt.row + drow[i];
                const ncol = pt.pt.col + dcol[i];
                if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and !visited[@intCast(nrow)][@intCast(ncol)]) {
                    visited[@intCast(nrow)][@intCast(ncol)] = true;
                    try queue.pushBack(
                        alloc,
                        .{ .pt = .{ .row = nrow, .col = ncol }, .dist = pt.dist + 1 },
                    );
                }
            }
        }
    }
}

/// Given a matrix mat of size N x M where every element is either ‘O’ or ‘X’.
/// Replace all ‘O’ with ‘X’ that is surrounded by ‘X’.
/// An ‘O’ (or a set of ‘O’) is considered to be surrounded by ‘X’ if there are ‘X’ at locations just below,
/// just above just left, and just right of it.
pub fn SurroundedRegions(
    alloc: Allocator,
    matrix: [][]u8,
    result: [][]u8,
) !void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    var visited: [][]bool = try alloc.alloc([]bool, n);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);
    for (0..n) |i| {
        // set visited[i]
        visited[i] = try alloc.alloc(bool, matrix[i].len);
        @memset(visited[i], false);
        for (0..matrix[i].len) |j|
            result[i][j] = matrix[i][j];
    }

    // from matrix[0][0]... matrix[0][n-1]
    for (0..m - 1) |i| {
        if (matrix[0][i] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(0), .col = @intCast(i) }, matrix, visited);
    }

    // from (matrix[1][m-1]...matrix[n-1][m-1])
    for (1..n - 1) |i| {
        if (matrix[i][m - 1] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(i), .col = @intCast(n - 1) }, matrix, visited);
    }

    // from (matrix[n-1][m-2]...matrix[n-1][0])
    for (0..m - 2) |i| {
        if (matrix[n - 1][m - 2 - i] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(n - 1), .col = @intCast(n - 2 - i) }, matrix, visited);
    }
    // from (matrix[n-2][0]..matrix[1][0])
    for (1..n - 2) |i| {
        if (matrix[n - 2 - i][0] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(n - 2 - i), .col = @intCast(0) }, matrix, visited);
    }

    for (0..n) |i| {
        for (0..matrix[i].len) |j| {
            if (!visited[i][j] and matrix[i][j] == 'O')
                result[i][j] = 'X';
        }
    }
}

fn surroundedRegionDfs(
    pt: Point,
    matrix: [][]u8,
    visited: [][]bool,
) void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    for (0..4) |i| {
        const nrow: i32 = @intCast(pt.row + drow[i]);
        const ncol: i32 = @intCast(pt.col + dcol[i]);
        if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and
            matrix[@intCast(nrow)][@intCast(ncol)] == 'O' and
            !visited[@intCast(nrow)][@intCast(ncol)] // if not visited
        ) {
            visited[@intCast(nrow)][@intCast(ncol)] = true;
            surroundedRegionDfs(.{ .row = nrow, .col = ncol }, matrix, visited);
        }
    }
}

/// You are given an N x M binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
/// A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
/// Find the number of land cells in the grid for which we cannot walk off the boundary of the grid in any number of moves..
pub fn NumberOfEnclaves() !void {
    // TODO
}

/// Given are the two distinct words startWord and targetWord, and a list denoting wordList of unique words of equal lengths.
/// Find the length of the shortest transformation sequence from startWord to targetWord..
/// In this problem statement, we need to keep the following conditions in mind:
///    - A word can only consist of lowercase characters.
///    - Only one letter can be changed in each transformation.
///    - Each transformed word must exist in the wordList including the targetWord.
///    - startWord may or may not be part of the wordList
pub fn WordLadder(
    alloc: Allocator,
    words: [][]const u8,
    source: []const u8,
    dist: []const u8,
) !usize {
    var wordmap = StringHashMap(void).init(alloc);
    defer wordmap.deinit();
    for (words) |word| try wordmap.put(word, {});

    var queue = try Deque(struct { word: []const u8, dist: usize }).initCapacity(alloc, 0);
    defer queue.deinit(alloc);
    try queue.pushBack(alloc, .{ .word = try alloc.dupe(u8, source), .dist = 1 });

    while (queue.len > 0) {
        const front = queue.popFront();
        if (front) |queue_data| {
            defer alloc.free(queue_data.word);
            if (std.mem.eql(u8, queue_data.word, dist)) {
                const distance = queue_data.dist;
                while (queue.popBack()) |f| alloc.free(f.word);
                return distance;
            }
            for (0..queue_data.word.len) |i| {
                var word = try alloc.dupe(u8, queue_data.word);
                defer alloc.free(word);

                for (0..26) |j| {
                    word[i] = 'a' + @as(u8, @intCast(j));
                    if (wordmap.contains(word)) {
                        _ = wordmap.remove(word);
                        try queue.pushBack(alloc, .{
                            .word = try alloc.dupe(u8, word),
                            .dist = queue_data.dist + 1,
                        });
                    }
                }
            }
        }
    }
    return 0;
}

/// Given a boolean 2D matrix grid of size N x M. You have to find the number of distinct islands where
/// a group of connected 1s (horizontally or vertically) forms an island. Two islands are considered
/// to be distinct if and only if one island
/// is equal to another (not rotated or reflected).
pub fn NumberOfIsland(
    alloc: Allocator,
    islands: [][]u8,
) !usize {
    var number_of_island: usize = 0;
    // no of rows
    const n = islands.len;
    // no of columns
    const m = islands[0].len;

    var visited: [][]bool = try alloc.alloc([]bool, n);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);
    for (0..n) |i| {
        visited[i] = try alloc.alloc(bool, islands[i].len);
        @memset(visited[i], false);
    }

    for (0..n) |row| {
        for (0..m) |col| {
            if (islands[row][col] == 1 and !visited[row][col]) {
                number_of_island += 1;
                var queue = try Deque(Point).initCapacity(alloc, 0);
                defer queue.deinit(alloc);
                try queue.pushBack(alloc, .{ .row = @intCast(row), .col = @intCast(col) });
                visited[row][col] = true;
                while (queue.len > 0) {
                    const front = queue.popBack();
                    if (front) |curr| {
                        for (0..4) |i| {
                            const nrow = curr.row + drow[i];
                            const ncol = curr.col + dcol[i];
                            if (nrow >= 0 and
                                nrow < n and
                                ncol >= 0 and
                                ncol < m and
                                !visited[@intCast(nrow)][@intCast(ncol)] and
                                islands[@intCast(nrow)][@intCast(ncol)] == 1)
                            {
                                visited[@intCast(nrow)][@intCast(ncol)] = true;
                                try queue.pushBack(alloc, .{ .row = @intCast(nrow), .col = @intCast(ncol) });
                            }
                        }
                    }
                }
            }
        }
    }
    return number_of_island;
}
