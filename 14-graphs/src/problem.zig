const std = @import("std");
const Io = std.Io;
const List = std.ArrayList;
const Allocator = std.mem.Allocator;

const core = @import("graphs.zig");

/// Graph Type
pub const Graph = core.Graph(u8, false);

/// data that is stored with node as intrusive
pub const Data = struct {
    data: u8,
    node: Graph.Node,
};

pub fn CreateGraph(graph: *Graph, datalist: *List(Data), allocator: Allocator) !void {
    try insertTograph(graph, datalist, allocator);
    try addEdges(graph, datalist);
}

fn insertTograph(graph: *Graph, datalist: *List(Data), allocator: Allocator) !void {
    for (65..75) |ch|
        try datalist.append(allocator, .{ .data = @intCast(ch), .node = .{ .index = null } });
    for (0..datalist.items.len) |i| try graph.insert(&(datalist.items[i].node));
}

//   g   a        h
//    \ / \        \
//     e---b---c    i
//    /   /
//   f   d        j
fn addEdges(graph: *Graph, datalist: *List(Data)) !void {
    const a = &(datalist.items[0].node);
    const b = &(datalist.items[1].node);
    const c = &(datalist.items[2].node);
    const d = &(datalist.items[3].node);
    const e = &(datalist.items[4].node);
    const f = &(datalist.items[5].node);
    const g = &(datalist.items[6].node);
    const h = &(datalist.items[7].node);
    const i = &(datalist.items[8].node);
    // a - b
    try graph.addEdge(a, b, 1);
    // a - c
    try graph.addEdge(a, e, 1);
    // b - c
    try graph.addEdge(b, c, 1);
    // b - d
    try graph.addEdge(b, d, 1);
    // b - e
    try graph.addEdge(b, e, 1);
    // e - f
    try graph.addEdge(e, f, 1);
    // e - g
    try graph.addEdge(e, g, 1);
    // h - i
    try graph.addEdge(h, i, 1);
}

pub const TestBed = struct {
    const Self = @This();

    graph: *Graph,
    allocator: Allocator,
    datalist: *List(Data),

    pub fn init(
        allocator: Allocator,
        graph: *Graph,
        datalist: *List(Data),
    ) Self {
        return .{
            .graph = graph,
            .allocator = allocator,
            .datalist = datalist,
        };
    }

    pub fn TestBfs(self: *Self) !void {
        std.debug.print("\n", .{});
        try self.graph.BfsTraversal({}, visit);
    }

    pub fn TestDfs(self: *Self) !void {
        std.debug.print("\nDFS\n\n", .{});
        try self.graph.DfsTraversal({}, visit);
    }

    pub fn TestShortestPath(self: *Self) !void {
        std.debug.print("\n", .{});
        try self.graph.shortestPath({}, shortest, &(self.datalist.items[0].node));
    }

    pub fn TestNumberOfProvisions(self: *Self) !void {
        const provisions = try self.graph.NumberOfProvinces();
        std.debug.print("Number of provisions : {d}\n", .{provisions});
    }

    pub fn TestDetectCycleUndirected(self: *Self) !void {
        const res = try  self.graph.DetectCycleUndirected() ;
        std.debug.print("{}\n", .{res});
    }

    pub fn TestRottenOranges(self: *Self) !void {
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

        const res = try core.RottenOranges(self.allocator, matrix[0..]);
        if (res) |t|
            std.debug.print("All the oranges rotten in {d}\n", .{t})
        else
            std.debug.print("All the oranges not rotten\n", .{});
    }

    pub fn TestFloodFill(self: *Self) !void {
        var rows = [_][3]u8{
            .{ 1, 2, 2 },
            .{ 2, 2, 1 },
            .{ 2, 1, 2 },
        };

        var matrix = [_][]u8{
            rows[0][0..],
            rows[1][0..],
            rows[2][0..],
        };
        try core.FloodFill(self.allocator, matrix[0..], 3, .{ .row = 2, .col = 0 });
        for (0..matrix.len) |i| std.debug.print("{any}\n", .{matrix[i]});
    }

    fn visit(_: void, node: *Graph.Node) !void {
        const data: *Data = @fieldParentPtr("node", @constCast(node));
        std.debug.print("{c}\n", .{data.data});
    }

    fn shortest(_: void, node: *Graph.Node, distance: usize) !void {
        const data: *Data = @fieldParentPtr("node", @constCast(node));
        std.debug.print("A to {c} : {d}\n", .{ data.data, distance });
    }
};
