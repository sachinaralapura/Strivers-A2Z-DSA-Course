// You are given an array of non-overlapping intervals intervals where intervals[i] = [starti, endi]
//  represent the start and the end of the ith interval and intervals is sorted in ascending order by starti.
//  You are also given an interval newInterval = [start, end] that represents the start and end of another interval.

// Insert newInterval into intervals such that intervals is still sorted in ascending order by
//  starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).

// Return intervals after the insertion.
const std = @import("std");
const Allocator = std.mem.Allocator;
const IntervalArray = std.ArrayList(Interval);
const Interval = @import("common.zig").Intervalt;

fn InsertInterval(allocator: Allocator, list: *IntervalArray, newInterval: Interval) !void {
    var leftIntervals: usize = 0;
    var rightInterval: usize = list.items.len + 1;
    for (list.items, 0..) |interval, i| {
        if (interval.end <= newInterval.start) leftIntervals = i + 1;
        if (interval.start >= newInterval.end) {
            rightInterval = i + 1;
            break;
        }
    }
    if (rightInterval == leftIntervals + 1) {
        try list.insert(allocator, leftIntervals, newInterval);
        return;
    }
    const newInt: Interval = .{
        .start = @min(newInterval.start, list.items[leftIntervals].start),
        .end = @max(newInterval.end, list.items[rightInterval - 1 - 1].end),
    };
    // delete the overlapping range
    try list.replaceRange(allocator, leftIntervals, (rightInterval - leftIntervals - 1), &[_]Interval{});
    // insert new interval
    try list.insert(allocator, leftIntervals, newInt);
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator: Allocator = gpa.allocator();
    var list = [_]Interval{
        .{ .start = 1, .end = 2 },
        .{ .start = 2, .end = 4 },
        .{ .start = 4, .end = 6 },
        .{ .start = 8, .end = 10 },
        .{ .start = 11, .end = 13 },
        .{ .start = 14, .end = 18 },
    };
    var intervals = try IntervalArray.initCapacity(allocator, 0);
    defer intervals.deinit(allocator);
    try intervals.insertSlice(allocator, 0, list[0..]);
    try InsertInterval(allocator, &intervals, .{ .start = 0, .end = 2 });
    for (intervals.items) |interval| {
        std.debug.print("{f}", .{interval});
    }
}
