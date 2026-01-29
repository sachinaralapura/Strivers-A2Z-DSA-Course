const std = @import("std");
const Io = std.Io;
const List = std.ArrayList;
const Allocator = std.mem.Allocator;

const core = @import("core");
const Graph = core.GraphType;
const Data = core.Data;
const TestBed = core.TestBed;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator: Allocator = gpa.allocator();

    var data_list = try List(Data).initCapacity(allocator, 0);
    defer data_list.deinit(allocator);

    var graph = try Graph.init(allocator);
    defer graph.deinit();

    try core.CreateGraph(&graph, &data_list, allocator);

    var testbed: TestBed = .init(allocator, &graph, &data_list);
    try testbed.TestDetectCycleUndirected();
}
