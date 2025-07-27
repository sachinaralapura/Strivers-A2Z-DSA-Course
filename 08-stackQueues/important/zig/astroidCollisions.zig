const std = @import("std");
const ArrayList = std.ArrayList(i32);
const Allocator = std.mem.Allocator;
const Stack = @import("Stack.zig").Stack(i32);
const Math = std.math;
var gpa = std.heap.GeneralPurposeAllocator(.{}).init;
fn AstroidCollistion(allocator: Allocator, arr: []const i32) !Stack {
    const n = arr.len;
    var stk: Stack = try Stack.init(allocator, n);
    for (arr) |ele| {
        if (ele > 0) try stk.push(ele) else {
            while (!stk.isEmpty() and stk.top().? > 0 and stk.top().? < @abs(ele)) {
                try stk.pop();
            }
            if (!stk.isEmpty() and stk.top().? == @abs(ele)) {
                try stk.pop();
            } else if (stk.isEmpty()) {
                try stk.push(ele);
            }
        }
    }
    return stk;
}
