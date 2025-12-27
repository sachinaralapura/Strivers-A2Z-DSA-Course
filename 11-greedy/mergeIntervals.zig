const std = @import("std");
const common = @import("common.zig");
const Sort = common.Sort;
const IntervalArray = common.ArrayList(Interval);
const Interval = common.Interval;
fn mergeInterval(list: []Interval, buffer: []Interval) !usize {
    Sort.insertion(Interval, list, {}, Interval.AscStart);
    var result = IntervalArray.initBuffer(buffer[0..]);
    try result.appendBounded(list[0]);
    for (1..list.len) |i|
        if (list[i].start < result.getLast().end) {
            result.items[result.items.len - 1].end = list[i].end;
        } else try result.appendBounded(list[i]);
    return result.items.len;
}

pub fn main() !void {
    var list = [6]Interval{
        .{ .start = 0, .end = 2 },
        .{ .start = 2, .end = 4 },
        .{ .start = 4, .end = 6 },
        .{ .start = 5, .end = 10 },
        .{ .start = 11, .end = 13 },
        .{ .start = 14, .end = 18 },
    };
    var result: [list.len + 1]Interval = undefined;
    const len = try mergeInterval(list[0..], result[0..]);
    for (0..len) |i| std.debug.print("{f}", .{result[i]});
}
