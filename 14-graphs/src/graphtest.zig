const std = @import("std");
const List = std.ArrayList;
const Allocator = std.mem.Allocator;
const core = @import("graphs.zig");
const expect = std.testing.expect;
const problems = @import("problems.zig");

/// Graph Type
pub const Graph = core.Graph(usize, false);
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

//  g.    .a        h
//    \  /  \.       \.
//     e.---b---.c    i
//   ./    /.
//   f     d        j
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
    const a = &(self.data_list.items[0].node); // 0
    const b = &(self.data_list.items[1].node); // 4
    const c = &(self.data_list.items[2].node); // 2
    const d = &(self.data_list.items[3].node); // 5
    const e = &(self.data_list.items[4].node); // 8
    const f = &(self.data_list.items[5].node); // 6
    const g = &(self.data_list.items[6].node); // 8
    const h = &(self.data_list.items[7].node); // 15
    const i = &(self.data_list.items[8].node); // 11
    const j = &(self.data_list.items[9].node); // 12

    try self.graph.addEdge(a, b, 4);
    try self.graph.addEdge(a, c, 2);
    try self.graph.addEdge(a, d, 7);

    try self.graph.addEdge(b, c, 1);
    try self.graph.addEdge(b, e, 5);

    try self.graph.addEdge(c, d, 3);
    try self.graph.addEdge(c, e, 6);
    try self.graph.addEdge(c, f, 4);

    try self.graph.addEdge(d, f, 2);
    try self.graph.addEdge(d, g, 8);

    try self.graph.addEdge(e, f, 1);
    try self.graph.addEdge(e, h, 7);

    try self.graph.addEdge(f, g, 2);

    try self.graph.addEdge(g, i, 3);

    try self.graph.addEdge(h, i, 4);
    try self.graph.addEdge(h, j, 6);

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

test "Eventual safe nodes" {
    const allocator = std.testing.allocator;
    var self: Self = try Self.init(allocator, true);
    defer self.deinit();

    try self.insertTograph();
    try self.createCyclicEdges();

    const expected = [7]*Graph.Node{
        self.graph.vertices.items[2], // C
        self.graph.vertices.items[3], // D
        self.graph.vertices.items[5], // F
        self.graph.vertices.items[6], // G
        self.graph.vertices.items[8], // I
        self.graph.vertices.items[9], // J
        self.graph.vertices.items[7], // H
    };
    const gen = struct {
        var i: usize = 0;
        var actual: [7]*Graph.Node = undefined;
        fn visit(_: void, node: *Graph.Node) !void {
            actual[i] = node;
            i += 1;
            // const data: *Data = @fieldParentPtr("node", @constCast(node));
            // std.debug.print("{c}\n", .{data.data});
        }
    };
    try self.graph.EventualSafeNodes({}, gen.visit);
    for (expected, 0..) |expected_value, i| try expect(expected_value == gen.actual[i]);
}

test "Shortest Distance in DAG" {
    const alloc = std.testing.allocator;
    var self: Self = try .init(alloc, true);
    defer self.deinit();

    try self.insertTograph();
    try self.createDAGEdges();

    const NodeDist = struct {
        node: *Graph.Node,
        dist: usize,
    };
    const expected = [10]NodeDist{
        .{ .node = self.graph.vertices.items[0], .dist = 0 }, // A
        .{ .node = self.graph.vertices.items[1], .dist = 4 }, // B
        .{ .node = self.graph.vertices.items[2], .dist = 2 }, // C
        .{ .node = self.graph.vertices.items[3], .dist = 5 }, // D
        .{ .node = self.graph.vertices.items[4], .dist = 8 }, // E
        .{ .node = self.graph.vertices.items[5], .dist = 6 }, // F
        .{ .node = self.graph.vertices.items[6], .dist = 8 }, // G
        .{ .node = self.graph.vertices.items[7], .dist = 15 }, // H
        .{ .node = self.graph.vertices.items[8], .dist = 11 }, // I
        .{ .node = self.graph.vertices.items[9], .dist = 12 }, // J
    };

    const gen = struct {
        var i: usize = 0;
        var actual: [10]NodeDist = undefined;
        fn visit(_: void, node: *Graph.Node, dist: usize) !void {
            actual[i] = .{ .node = node, .dist = dist };
            i += 1;
            // const data: *Data = @fieldParentPtr("node", @constCast(node));
            // std.debug.print("{c} : {d}\n", .{ data.data, dist });
        }
    };

    try self.graph.ShortestPathInDAG({}, gen.visit);
    for (expected, 0..) |expected_value, i| try expect(expected_value.node == gen.actual[i].node);
    for (expected, 0..) |expected_value, i| try expect(expected_value.dist == gen.actual[i].dist);
}

fn createDijkstraEdges(self: *Self) !void {
    const a = &(self.data_list.items[0].node); // 0
    const b = &(self.data_list.items[1].node); // 4
    const c = &(self.data_list.items[2].node); // 2
    const d = &(self.data_list.items[3].node); // 5
    const e = &(self.data_list.items[4].node); // 8
    const f = &(self.data_list.items[5].node); // 6
    const g = &(self.data_list.items[6].node); // 8
    const h = &(self.data_list.items[7].node); // 15
    const i = &(self.data_list.items[8].node); // 11
    const j = &(self.data_list.items[9].node); // 12

    try self.graph.addEdge(a, b, 6);
    try self.graph.addEdge(a, d, 2);

    try self.graph.addEdge(b, c, 4);
    try self.graph.addEdge(b, e, 7);

    try self.graph.addEdge(c, d, 3);
    try self.graph.addEdge(c, e, 4);
    try self.graph.addEdge(c, f, 4);

    try self.graph.addEdge(d, f, 5);
    try self.graph.addEdge(d, g, 5);

    try self.graph.addEdge(e, f, 1);
    try self.graph.addEdge(e, h, 5);

    try self.graph.addEdge(f, g, 2);

    try self.graph.addEdge(g, i, 3);
    try self.graph.addEdge(g, j, 4);

    try self.graph.addEdge(h, i, 4);
    try self.graph.addEdge(h, j, 8);

    try self.graph.addEdge(i, j, 6);
}

// test "Dijkstra" {
//     const alloc = std.testing.allocator;
//     var self: Self = try .init(alloc, false);
//     defer self.deinit();

//     try self.insertTograph();
//     try self.createDijkstraEdges();
//     const gen = struct {
//         fn visit(_: void, node: *Graph.Node) !void {
//             const data: *Data = @fieldParentPtr("node", @constCast(node));
//             std.debug.print("{c}\n", .{data.data});
//         }
//     };

//     try self.graph.DijkstraUndirected(self.graph.vertices.items[0], self.graph.vertices.items[7], {}, gen.visit);
// }

fn CreateCheapestFlightGraph(self: *Self) !void {
    const a = &(self.data_list.items[0].node); // 0
    const b = &(self.data_list.items[1].node); // 4
    const c = &(self.data_list.items[2].node); // 2
    const d = &(self.data_list.items[3].node); // 5
    const e = &(self.data_list.items[4].node); // 8
    try self.graph.addEdge(a, b, 5);
    try self.graph.addEdge(a, d, 2);
    try self.graph.addEdge(b, c, 5);
    try self.graph.addEdge(b, e, 1);
    try self.graph.addEdge(d, b, 2);
    try self.graph.addEdge(e, c, 1);
}

test "Cheapest flight" {
    const alloc = std.testing.allocator;
    var self: Self = try .init(alloc, true);
    defer self.deinit();
    try self.insertTograph();
    try self.CreateCheapestFlightGraph();

    const res = try problems.CheapestFlight(
        alloc,
        &self.graph,
        2,
        self.graph.vertices.items[0],
        self.graph.vertices.items[2],
    );

    try expect(null != res);
    if (res) |r| try expect(7 == r);
}

fn createNumberOfWaysToArrive(self: *Self) !void {
    const a = &(self.data_list.items[0].node); // 0
    const b = &(self.data_list.items[1].node); // 1
    const c = &(self.data_list.items[2].node); // 2
    const d = &(self.data_list.items[3].node); // 3
    const e = &(self.data_list.items[4].node); // 4
    const f = &(self.data_list.items[5].node); // 5
    const g = &(self.data_list.items[6].node); // 6
    const h = &(self.data_list.items[7].node); // 7
    const i = &(self.data_list.items[8].node); // 8
    // const j = &(self.data_list.items[9].node); // 12

    try self.graph.addEdge(a, b, 1);
    try self.graph.addEdge(a, c, 2);
    try self.graph.addEdge(a, d, 1);
    try self.graph.addEdge(a, e, 2);

    try self.graph.addEdge(b, f, 2);

    try self.graph.addEdge(c, f, 1);

    try self.graph.addEdge(d, f, 2);
    try self.graph.addEdge(d, h, 3);
    try self.graph.addEdge(d, g, 2);

    try self.graph.addEdge(e, g, 1);

    try self.graph.addEdge(f, i, 1);

    try self.graph.addEdge(g, i, 1);

    try self.graph.addEdge(h, i, 1);
}

test "Number of ways to arrive" {
    const alloc = std.testing.allocator;
    var self: Self = try .init(alloc, true);
    defer self.deinit();
    try self.insertTograph();
    try self.createNumberOfWaysToArrive();

    const a = &(self.data_list.items[0].node); // 0
    const i = &(self.data_list.items[8].node); // 8
    const res = try self.graph.NumberOfWaysToArrive(a, i);
    try expect(5 == res);
}

test "Bellmanford" {
    const alloc = std.testing.allocator;
    const GraphBellmanFord = core.Graph(i64, true);
    var graph = try GraphBellmanFord.init(alloc);
    defer graph.deinit();

    var data_list: List(Data) = try .initCapacity(alloc, 0);
    defer data_list.deinit(alloc);

    for (0..6) |ch|
        try data_list.append(alloc, .{ .data = @intCast(ch), .node = .{ .index = null } });
    for (0..data_list.items.len) |i| try graph.insert(&(data_list.items[i].node));

    const zero = &(data_list.items[0].node); // 0
    const one = &(data_list.items[1].node); // 1
    const two = &(data_list.items[2].node); // 2
    const three = &(data_list.items[3].node); // 3
    const four = &(data_list.items[4].node); // 4
    const five = &(data_list.items[5].node); // 5

    try graph.addEdge(zero, one, 5);

    try graph.addEdge(one, five, -3);

    try graph.addEdge(one, two, -2);

    try graph.addEdge(five, three, 1);

    try graph.addEdge(three, two, 6);

    try graph.addEdge(two, four, 3);

    try graph.addEdge(three, four, -2);
    const NodeDist = struct {
        node: *GraphBellmanFord.Node,
        dist: i64,
    };
    const expected = [6]NodeDist{
        .{ .node = zero, .dist = 0 },
        .{ .node = one, .dist = 5 },
        .{ .node = two, .dist = 3 },
        .{ .node = three, .dist = 3 },
        .{ .node = four, .dist = 1 },
        .{ .node = five, .dist = 2 },
    };
    const gen = struct {
        var i: usize = 0;
        var actual: [6]NodeDist = undefined;
        fn visit(_: void, node: *Graph.Node, dist: i64) !void {
            actual[i] = .{ .node = node, .dist = dist };
            i += 1;
        }
    };
    try expect(graph.Bellmanford(zero, {}, gen.visit) != GraphBellmanFord.Error.NegativeCycle);
    for (expected, 0..) |nd, i| {
        try expect(nd.node == gen.actual[i].node);
        try expect(nd.dist == gen.actual[i].dist);
    }
}

test "FloydWarshell Algorithm" {
    const alloc = std.testing.allocator;
    const W = i64;
    const GraphFloyd = core.Graph(W, true);
    var graph = try GraphFloyd.init(alloc);
    defer graph.deinit();

    var data_list: List(Data) = try .initCapacity(alloc, 0);
    defer data_list.deinit(alloc);

    for (0..5) |ch|
        try data_list.append(alloc, .{ .data = @intCast(ch), .node = .{ .index = null } });
    for (0..data_list.items.len) |i| try graph.insert(&(data_list.items[i].node));

    const zero = &(data_list.items[0].node); // 0
    const one = &(data_list.items[1].node); // 1
    const two = &(data_list.items[2].node); // 2
    const three = &(data_list.items[3].node); // 3
    const four = &(data_list.items[4].node); // 4

    try graph.addEdge(zero, one, 4);
    try graph.addEdge(zero, three, 5);

    try graph.addEdge(one, four, 6);
    try graph.addEdge(one, two, 1);

    try graph.addEdge(two, zero, 2);
    try graph.addEdge(two, three, 3);

    try graph.addEdge(three, two, 1);
    try graph.addEdge(three, four, 2);

    try graph.addEdge(four, three, 4);
    try graph.addEdge(four, zero, 1);

    const adjacenyMatrix = try alloc.alloc([]W, graph.vertices.items.len);
    defer alloc.free(adjacenyMatrix);
    defer for (0..adjacenyMatrix.len) |i| alloc.free(adjacenyMatrix[i]);
    for (adjacenyMatrix, 0..) |*row, i| {
        row.* = try alloc.alloc(W, graph.vertices.items.len);
        @memset(row.*, std.math.maxInt(W));
        row.*[i] = 0;
    }
    const expected = [5][5]W{
        .{ 0, 4, 5, 5, 7 },
        .{ 3, 0, 1, 4, 6 },
        .{ 2, 6, 0, 3, 5 },
        .{ 3, 7, 1, 0, 2 },
        .{ 1, 5, 5, 4, 0 },
    };
    for (0..expected.len) |i| {
        for (0..expected.len) |j| {
            adjacenyMatrix[i][j] = expected[i][j];
        }
    }
    const Ctx = struct { expected: [][]W };
    const gen = struct {
        fn visit(ctx: Ctx, source: *GraphFloyd.Node, dest: *GraphFloyd.Node, dist: W) !void {
            try expect(ctx.expected[source.index.?][dest.index.?] == dist);
        }
    };
    try graph.FloydWarshallAlgorithm(Ctx{ .expected = adjacenyMatrix }, gen.visit);
}
