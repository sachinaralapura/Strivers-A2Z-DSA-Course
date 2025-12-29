const std = @import("std");
const root = @import("binarytree");
const Allocator = std.mem.Allocator;
const BinaryTree = root.BinaryTree;
const Node = root.Node;
const BTT = usize;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator: Allocator = gpa.allocator();
    var binaryTree = BinaryTree(BTT).init(allocator);
    defer binaryTree.deinit();
    for (1..8) |i| try binaryTree.insert(i);
    const height = binaryTree.height();
    std.debug.print("height of tree : {d}\n", .{height});
    std.debug.print("{}", .{binaryTree.isBalanced()});
    std.debug.print("{}", .{binaryTree.maxDiameter()});
}
