const std = @import("std");
const List = std.ArrayList;
const Allocator = std.mem.Allocator;
const core = @import("graphs.zig");
const expect = std.testing.expect;

/// Graph Type
pub const Graph = core.Graph(u8, false);
/// data that is stored with node as intrusive
pub const Data = struct {
    data: u8,
    node: Graph.Node,
};

const Self = @This();

graph: Graph,
data_list: List(Data),
allocator: Allocator,

fn init(allocator: Allocator, is_directed: bool) !Self {
    return .{
        .graph = try Graph.initDirected(allocator, is_directed),
        .data_list = try List(Data).initCapacity(allocator, 0),
        .allocator = allocator,
    };
}

fn deinit(self: *Self) void {
    self.data_list.deinit(self.allocator);
    self.graph.deinit();
}

//   g   a        h
//    \ / \        \
//     e---b---c    i
//    /   /
//   f   d        j
fn insertTograph(self: *Self) !void {
    for (65..75) |ch|
        try self.data_list.append(self.allocator, .{ .data = @intCast(ch), .node = .{ .index = null } });
    for (0..self.data_list.items.len) |i| try self.graph.insert(&(self.data_list.items[i].node));
}
fn addEdges(self: *Self) !void {
    const a = &(self.data_list.items[0].node);
    const b = &(self.data_list.items[1].node);
    const c = &(self.data_list.items[2].node);
    const d = &(self.data_list.items[3].node);
    const e = &(self.data_list.items[4].node);
    const f = &(self.data_list.items[5].node);
    const g = &(self.data_list.items[6].node);
    const h = &(self.data_list.items[7].node);
    const i = &(self.data_list.items[8].node);
    // const j = &(self.data_list.items[9].node);

    // a - b
    try self.graph.addEdge(a, b, 1);
    // a - c
    try self.graph.addEdge(a, e, 1);
    // b - c
    try self.graph.addEdge(b, c, 1);
    // b - d
    try self.graph.addEdge(b, d, 1);
    // b - e
    try self.graph.addEdge(b, e, 1);
    // e - f
    try self.graph.addEdge(e, f, 1);
    // e - g
    try self.graph.addEdge(e, g, 1);
    // h - i
    try self.graph.addEdge(h, i, 1);
}

fn visit(_: void, node: *Graph.Node) !void {
    const data: *Data = @fieldParentPtr("node", @constCast(node));
    std.debug.print("{c}\n", .{data.data});
}

test "CreateGraph" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();

    // test vertices
    for (0..10) |i| {
        const data: *Data = @fieldParentPtr("node", self.graph.vertices.items[i]);
        try expect(data.data == 65 + i);
    }

    // test edges
    const b = self.graph.vertices.items[1];
    const c = self.graph.vertices.items[2];
    const d = self.graph.vertices.items[3];
    const e = self.graph.vertices.items[4];
    const f = self.graph.vertices.items[5];
    const g = self.graph.vertices.items[6];
    const i = self.graph.vertices.items[8];

    const a_adj = self.graph.adj.items[0];
    try expect(a_adj.items[0].destination == b);
    try expect(a_adj.items[1].destination == e);

    const b_adj = self.graph.adj.items[1];
    try expect(b_adj.items[0].destination == c);
    try expect(b_adj.items[1].destination == d);

    const e_adj = self.graph.adj.items[4];
    try expect(e_adj.items[0].destination == f);
    try expect(e_adj.items[1].destination == g);

    const h_adj = self.graph.adj.items[7];
    try expect(h_adj.items[0].destination == i);
}

test "BFS" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();

    const expected = [7]*Graph.Node{
        self.graph.vertices.items[0], // A
        self.graph.vertices.items[1], // B
        self.graph.vertices.items[4], // E
        self.graph.vertices.items[2], // C
        self.graph.vertices.items[3], // D
        self.graph.vertices.items[5], // F
        self.graph.vertices.items[6], // G
    };

    const gen = struct {
        var i: usize = 0;
        var actual: [7]*Graph.Node = undefined;

        fn visit(_: void, node: *Graph.Node) !void {
            actual[i] = node;
            i += 1;
        }
    };

    try self.graph.BfsTraversal({}, gen.visit);
    for (expected, 0..) |expected_value, i| try expect(expected_value == gen.actual[i]);
}

test "DFS" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();

    const expected = [10]*Graph.Node{
        self.graph.vertices.items[0], // A
        self.graph.vertices.items[1], // B
        self.graph.vertices.items[2], // C
        self.graph.vertices.items[3], // D
        self.graph.vertices.items[4], // E
        self.graph.vertices.items[5], // F
        self.graph.vertices.items[6], // G
        self.graph.vertices.items[7], // H
        self.graph.vertices.items[8], // I
        self.graph.vertices.items[9], // J
    };

    const gen = struct {
        var i: usize = 0;
        var actual: [10]*Graph.Node = undefined;

        fn visit(_: void, node: *Graph.Node) !void {
            actual[i] = node;
            i += 1;
        }
    };

    try self.graph.DfsTraversal({}, gen.visit);
    for (expected, 0..) |expected_value, i| try expect(expected_value == gen.actual[i]);
}

test "Shortestpath" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, false);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();
    const expected = [7]struct {
        node: *Graph.Node,
        dist: usize,
    }{
        .{ .node = self.graph.vertices.items[0], .dist = 0 }, // A
        .{ .node = self.graph.vertices.items[1], .dist = 1 }, // B
        .{ .node = self.graph.vertices.items[4], .dist = 1 }, // E
        .{ .node = self.graph.vertices.items[2], .dist = 2 }, // C
        .{ .node = self.graph.vertices.items[3], .dist = 2 }, // D
        .{ .node = self.graph.vertices.items[5], .dist = 2 }, // F
        .{ .node = self.graph.vertices.items[6], .dist = 2 }, // G
    };

    const gen = struct {
        var i: usize = 0;
        var actual: [7]struct { node: *Graph.Node, dist: usize } = undefined;
        fn shortest(_: void, node: *Graph.Node, distance: usize) !void {
            actual[i] = .{ .node = node, .dist = distance };
            i += 1;
        }
    };

    try self.graph.shortestPath({}, gen.shortest, &(self.data_list.items[0].node));
    for (expected, 0..) |expected_struct, i| {
        try expect(expected_struct.node == gen.actual[i].node);
        try expect(expected_struct.dist == gen.actual[i].dist);
    }
}

test "Number of provisions" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, false);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();

    const expected: usize = 3;
    const actual = try self.graph.NumberOfProvinces();
    try expect(expected == actual);
}

test "TestDetectCycleUndirected" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, false);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();

    try expect(true == try self.graph.DetectCycleUndirected());
    try expect(true == try self.graph.DetectCycleUndirectedDfs());
}

test "Rotten Oranges" {
    const allocator = std.testing.allocator;
    var rows = [_][3]u8{
        .{ 0, 1, 2 },
        .{ 0, 1, 1 },
        .{ 2, 1, 1 },
    };
    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
    };
    const expected: usize = 2;
    const actual = try core.RottenOranges(allocator, matrix[0..]);
    try expect(expected == actual);
}

test "FloodFill" {
    const allocator = std.testing.allocator;
    var rows = [_][3]u8{ .{ 1, 2, 2 }, .{ 2, 2, 1 }, .{ 2, 1, 2 } };
    var matrix = [_][]u8{ rows[0][0..], rows[1][0..], rows[2][0..] };

    var expected = [_][3]u8{ .{ 1, 3, 3 }, .{ 3, 3, 1 }, .{ 3, 1, 2 } };

    try core.FloodFill(
        allocator,
        matrix[0..],
        3,
        .{ .row = 2, .col = 0 },
    );

    for (0..matrix.len) |i|
        for (0..matrix.len) |j|
            try expect(matrix[i][j] == expected[i][j]);
}

test "OneDistance" {
    const allocator = std.testing.allocator;

    var rows = [_][3]u8{
        .{ 0, 0, 0 },
        .{ 0, 1, 0 },
        .{ 1, 0, 1 },
    };
    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
    };

    // result
    var result: [][]usize = try allocator.alloc([]usize, matrix.len);
    for (result, 0..) |*row, i| {
        row.* = try allocator.alloc(usize, matrix[i].len);
        @memset(row.*, 0);
    }
    defer allocator.free(result);
    defer for (0..result.len) |i| allocator.free(result[i]);

    var expected = [_][3]u8{
        .{ 2, 1, 2 },
        .{ 1, 0, 1 },
        .{ 0, 1, 0 },
    };
    try core.OneDistance(allocator, matrix[0..], result);

    for (0..result.len) |i|
        for (0..result.len) |j|
            try expect(result[i][j] == expected[i][j]);
}

test "SurroundRegions" {
    const allocator = std.testing.allocator;

    const X: u8 = 'X';
    const O: u8 = 'O';
    var rows = [_][4]u8{
        .{ X, X, X, X },
        .{ X, O, O, X },
        .{ X, O, X, X },
        .{ X, O, X, X },
        .{ X, X, O, O },
    };

    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
        rows[3][0..],
        rows[4][0..],
    };

    var result: [][]u8 = try allocator.alloc([]u8, matrix.len);
    for (result, 0..) |*row, i| {
        row.* = try allocator.alloc(u8, matrix[i].len);
        @memset(row.*, 0);
    }
    defer allocator.free(result);
    defer for (0..result.len) |i| allocator.free(result[i]);

    try core.SurroundedRegions(allocator, matrix[0..], result);

    var expected = [_][4]u8{
        .{ X, X, X, X },
        .{ X, X, X, X },
        .{ X, X, X, X },
        .{ X, X, X, X },
        .{ X, X, O, O },
    };

    for (0..result.len) |i|
        for (0..result[i].len) |j|
            try expect(result[i][j] == expected[i][j]);
}

test "WordLadder" {
    const allocator = std.testing.allocator;
    var words = [_][]const u8{ "des", "der", "dfr", "dgt", "dfs" };
    const source = "der";
    const dist = "dfs";
    const res = try core.WordLadder(allocator, &words, source, dist);
    try expect(3 == res);
}

test "NumberOfIsland" {
    const allocator = std.testing.allocator;

    var rows = [_][5]u8{
        .{ 1, 1, 0, 1, 1 },
        .{ 1, 0, 0, 0, 0 },
        .{ 0, 0, 0, 0, 1 },
        .{ 1, 1, 0, 1, 1 },
    };

    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
        rows[3][0..],
    };

    const expected = try core.NumberOfIsland(allocator, matrix[0..]);
    try expect(4 == expected);
}

test "IsBipartite" {
    const allocator = std.testing.allocator;
    var self: Self = try .init(allocator, false);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();
    // _ = try self.graph.IsBipartiteGraph();
    try expect(false == try self.graph.IsBipartiteGraph());
}
