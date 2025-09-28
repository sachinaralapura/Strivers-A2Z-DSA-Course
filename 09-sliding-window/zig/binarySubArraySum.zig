const std = @import("std");
fn temp(arr: []const u8, goal: usize) usize {
    if (goal < 0) return 0;
    var sum: usize = 0;
    var count: usize = 0;
    var left: usize = 0;
    var right: usize = 0;
    while (right < arr.len) {
        sum += arr[right];
        while (sum > goal) {
            sum = sum - arr[left];
            left = left + 1;
        }
        count = count + (right - left + 1);
        right = right + 1;
    }
    return count;
}

pub fn binSubArraySum(arr: []const u8, goal: usize) usize {
    return temp(arr, goal) - temp(arr, goal - 1);
}

pub fn main() !void {
    const arr = [_]u8{ 1, 0, 1, 0, 1 };
    const count: usize = binSubArraySum(&arr, 2);
    std.debug.print("count : {d}\n", .{count});
}
