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

    var binaryTreeTwo = BinaryTree(BTT).init(allocator);
    defer binaryTreeTwo.deinit();

    // for (1..17) |i| try binaryTree.insert(i);
    for (1..16) |i| try binaryTreeTwo.insert(i);

    const height = binaryTree.height();

    std.debug.print("height of tree : {d}\n", .{height});
    std.debug.print("{}\n", .{binaryTree.isBalanced()});
    std.debug.print("{}\n", .{binaryTree.maxDiameter()});
    std.debug.print("{}\n", .{binaryTree.maxSumPath()});

    if (binaryTree.identical(&binaryTreeTwo)) {
        std.debug.print("Two tree are identical\n", .{});
    } else std.debug.print("Two tree are not identical\n", .{});

    try binaryTree.zigZag(visit, false);
}

fn visit(data: BTT) void {
    std.debug.print("{d}\t", .{data});
}
