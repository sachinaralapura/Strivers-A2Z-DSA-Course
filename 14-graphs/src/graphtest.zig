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

test "IsBipartite" {
    const allocator = std.testing.allocator;
    var self: Self = try .init(allocator, false);
    defer self.deinit();

    try self.insertTograph();
    try self.addEdges();
    // _ = try self.graph.IsBipartiteGraph();
    try expect(false == try self.graph.IsBipartiteGraph());
}

//  g.    a        h
//    \ ./  \.       \.
//     e.---b---c    i
//   ./   ./
//   f    d        j
fn createCyclicEdges(self: *Self) !void {
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
    try self.graph.addEdge(e, a, 1);
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

test "Detect cycle directed DFS" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.createCyclicEdges();

    try expect(true == try self.graph.DetectCycleDirectedDfs());
}

test "Detect cycle directed BFS" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.createCyclicEdges();

    try expect(true == try self.graph.DetectCycleDirectedBfs());
}

fn createDAGEdges(self: *Self) !void {
    const a = &(self.data_list.items[0].node);
    const b = &(self.data_list.items[1].node);
    const c = &(self.data_list.items[2].node);
    const d = &(self.data_list.items[3].node);
    const e = &(self.data_list.items[4].node);
    const f = &(self.data_list.items[5].node);
    const g = &(self.data_list.items[6].node);
    const h = &(self.data_list.items[7].node);
    const i = &(self.data_list.items[8].node);
    const j = &(self.data_list.items[9].node);

    try self.graph.addEdge(a, b, 1);
    try self.graph.addEdge(a, e, 1);
    try self.graph.addEdge(a, d, 1);

    try self.graph.addEdge(b, c, 1);
    try self.graph.addEdge(b, e, 1);

    try self.graph.addEdge(c, d, 1);
    try self.graph.addEdge(c, e, 1);
    try self.graph.addEdge(c, f, 1);

    try self.graph.addEdge(d, f, 1);
    try self.graph.addEdge(d, g, 1);

    try self.graph.addEdge(e, f, 1);
    try self.graph.addEdge(e, h, 1);

    try self.graph.addEdge(f, g, 1);

    try self.graph.addEdge(g, i, 1);

    try self.graph.addEdge(h, i, 1);
    try self.graph.addEdge(h, j, 1);

    try self.graph.addEdge(i, j, 1);
}

test "Topologica Sort DFS" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.createDAGEdges();

    const expected = [10]*Graph.Node{
        self.graph.vertices.items[0], // A
        self.graph.vertices.items[1], // B
        self.graph.vertices.items[2], // C
        self.graph.vertices.items[4], // E
        self.graph.vertices.items[7], // H
        self.graph.vertices.items[3], // D
        self.graph.vertices.items[5], // F
        self.graph.vertices.items[6], // G
        self.graph.vertices.items[8], // I
        self.graph.vertices.items[9], // J
    };

    const gen = struct {
        var i: usize = 0;
        var actual: [10]*Graph.Node = undefined;
        fn visit(_: void, node: *Graph.Node) !void {
            actual[i] = node;
            i += 1;
            // const data: *Data = @fieldParentPtr("node", @constCast(node));
            // std.debug.print("{c}\n", .{data.data});
        }
    };

    try self.graph.TopologicalSortDfs({}, gen.visit);
    for (expected, 0..) |expected_value, i| try expect(expected_value == gen.actual[i]);
}

test "Topological Sort BFS" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.createDAGEdges();

    const expected = [10]*Graph.Node{
        self.graph.vertices.items[0], // A
        self.graph.vertices.items[1], // B
        self.graph.vertices.items[2], // C
        self.graph.vertices.items[3], // D
        self.graph.vertices.items[4], // E
        self.graph.vertices.items[5], // F
        self.graph.vertices.items[7], // H
        self.graph.vertices.items[6], // G
        self.graph.vertices.items[8], // I
        self.graph.vertices.items[9], // J
    };
    const gen = struct {
        var i: usize = 0;
        var actual: [10]*Graph.Node = undefined;
        fn visit(_: void, node: *Graph.Node) !void {
            actual[i] = node;
            i += 1;
            // const data: *Data = @fieldParentPtr("node", @constCast(node));
            // std.debug.print("{c}\n", .{data.data});
        }
    };

    try self.graph.TopologicalSortBfs({}, gen.visit);
    for (expected, 0..) |expected_value, i| try expect(expected_value == gen.actual[i]);
}
