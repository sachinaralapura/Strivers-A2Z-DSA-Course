const std = @import("std");
const binarySubArraySum = @import("binarySubArraySum.zig");

// Given an array of integers nums and an integer k.
// A continuous subarray is called nice if there are k odd numbers on it.
pub fn main() !void {
    const arr = [_]usize{ 2,2,2,1,2,2,1,2,2,2 };
    var binArray: [arr.len]u8 = undefined;
    for (arr, 0..) |value, i| {
        const is_odd = value % 2 != 0;
        binArray[i] = @intFromBool(is_odd);
    }
    const count = binarySubArraySum.binSubArraySum(&binArray, 2);
    std.debug.print("count : {d}\n", .{count});
}
