// Problem Statement: There is one meeting room in a firm.
// You are given two arrays, start and end each of size N.
// For an index ‘i’, start[i] denotes the starting time of
// the ith meeting while end[i] will denote the ending time of the ith meeting.
// Find the maximum number of meetings that can be accommodated if only
// one meeting can happen in the room at a particular time.
// Print the order in which these meetings will be performed.

const std = @import("std");
const Allocator = std.mem.Allocator;
const common = @import("common.zig");
const Sort = common.Sort;
const Meeting = common.Meeting;
const MeetingList = common.MeetingList;
const MeetingOrder = common.MeetingOrder;

fn NMeetings(allocator: Allocator, meetings: []Meeting) ![]Meeting {
    Sort.insertion(Meeting, meetings, {}, MeetingOrder);
    var result = try MeetingList.initCapacity(allocator, 0);
    var last_occupied_time = meetings[0].end;
    try result.append(allocator, meetings[0]);
    for (1..meetings.len) |i| {
        if (meetings[i].start > last_occupied_time) {
            try result.append(allocator, meetings[i]);
            last_occupied_time = meetings[i].end;
        }
    }
    return try result.toOwnedSlice(allocator);
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    var meeetings = [_]Meeting{
        .{ .start = 0, .end = 5 },
        .{ .start = 1, .end = 2 },
        .{ .start = 3, .end = 4 },
        .{ .start = 5, .end = 7 },
        .{ .start = 5, .end = 9 },
        .{ .start = 8, .end = 9 },
    };

    std.debug.print("START : ", .{});
    for (meeetings) |meeting| std.debug.print(" {d} |", .{meeting.start});
    std.debug.print("\n", .{});

    std.debug.print("END   : ", .{});
    for (meeetings) |meeting| std.debug.print(" {d} |", .{meeting.end});
    std.debug.print("\n", .{});

    const result = try NMeetings(allocator, &meeetings);
    std.debug.print("\n", .{});

    std.debug.print("START : ", .{});
    for (result) |meeting| std.debug.print(" {d} |", .{meeting.start});
    std.debug.print("\n", .{});

    std.debug.print("END   : ", .{});
    for (result) |meeting| std.debug.print(" {d} |", .{meeting.end});
    std.debug.print("\n", .{});
    defer allocator.free(result);
}
