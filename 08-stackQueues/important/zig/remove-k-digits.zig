const std = @import("std");
const Stack = @import("Stack.zig").Stack(i32);
const Allocoator = std.mem.Allocator;
const ArrayList = std.ArrayList(u8);
var gpa = std.heap.GeneralPurposeAllocator(.{}).init;

fn removeKDigits(allocoator: Allocoator, num: []const u8, limit: u32) ![]const u8 {
    var stk = try Stack.init(allocoator, num.len);
    var k: u32 = limit;
    var res = ArrayList.init(allocoator);
    defer res.deinit();
    for (num) |value| {
        while (!stk.isEmpty() and k > 0 and stk.top().? > value) {
            try stk.pop();
            k = k - 1;
        }
        try stk.push(value);
    }
    while (k > 0 and !stk.isEmpty()) {
        try stk.pop();
        k = k - 1;
    }
    if (stk.isEmpty()) return "0";

    for (stk.items[0..stk.length]) |value| {
        const temp: u8 = @intCast(value);
        try res.append(temp);
    }
    return res.toOwnedSlice();
}

// pub fn main() !void {
//     const allocator = gpa.allocator();
//     const num = "141234";
//     const k: u32 = 3;
//     const res = try removeKDigits(allocator, num, k);
//     defer allocator.free(res);
//     std.debug.print("{s}", .{res});
// }
