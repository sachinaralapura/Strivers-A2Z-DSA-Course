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
    // const j = &(datalist.items[9].node);

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
    // i - j
    // try graph.addEdge(i, j, 1);
    // h - j
    // try graph.addEdge(j, h, 1);
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
        const res = try self.graph.DetectCycleUndirected();
        std.debug.print("{}\n", .{res});
    }

    pub fn TestDetectCycleUndirectedDfs(self: *Self) !void {
        const res = try self.graph.DetectCycleUndirectedDfs();
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

    pub fn TestOneDistance(self: *Self) !void {
        // matrix
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
        var result: [][]usize = try self.allocator.alloc([]usize, matrix.len);
        for (result, 0..) |*row, i| {
            row.* = try self.allocator.alloc(usize, matrix[i].len);
            @memset(row.*, 0);
        }
        defer self.allocator.free(result);
        defer for (0..result.len) |i| self.allocator.free(result[i]);

        try core.OneDistance(self.allocator, matrix[0..], result);

        for (0..result.len) |i| {
            for (0..result[i].len) |j| std.debug.print("{d},", .{result[i][j]});
            std.debug.print("\n", .{});
        }
    }

    pub fn TestSurroundRegions(self: *Self) !void {
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

        var result: [][]u8 = try self.allocator.alloc([]u8, matrix.len);
        for (result, 0..) |*row, i| {
            row.* = try self.allocator.alloc(u8, matrix[i].len);
            @memset(row.*, 0);
        }
        defer self.allocator.free(result);
        defer for (0..result.len) |i| self.allocator.free(result[i]);

        for (0..matrix.len) |i| {
            for (0..matrix[i].len) |j| std.debug.print("{c},", .{matrix[i][j]});
            std.debug.print("\n", .{});
        }

        std.debug.print("\n", .{});

        try core.SurroundedRegions(self.allocator, matrix[0..], result);

        for (0..result.len) |i| {
            for (0..result[i].len) |j| std.debug.print("{c},", .{result[i][j]});
            std.debug.print("\n", .{});
        }
    }

    pub fn TestWordLadder(self: *Self) !void {
        var words = [_][]const u8{ "des", "der", "dfr", "dgt", "dfs" };
        const source = "der";
        const dist = "dfs";
        const res = try core.WordLadder(self.allocator, &words, source, dist);
        std.debug.print("{d}\n", .{res});
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
