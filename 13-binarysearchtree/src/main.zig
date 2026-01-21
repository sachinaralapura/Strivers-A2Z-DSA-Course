const std = @import("std");
const core = @import("core");

const BST = core.BinarySearchTree;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const allocator = gpa.allocator();

    var bst = BST(i32, null).init(allocator);
    defer bst.deinit();

    for ([_]usize{ 5, 3, 7, 1, 4, 6, 8, 2 }) |i| try bst.insert(@intCast(i));

    const max = bst.search(10);
    if (max) |m| std.debug.print("{f}\n", .{m});

    const kth = bst.KthLargest(10);
    if (kth) |k| std.debug.print("kth : {d}\n", .{k});

    const valid = bst.ValidBST(null);
    std.debug.print("valid bst {}\n", .{valid});

}

fn order(_: void, data: i32) !void {
    std.debug.print("{d}, ", .{data});
}
