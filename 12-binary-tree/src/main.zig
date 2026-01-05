const std = @import("std");
const root = @import("binarytree");
const Allocator = std.mem.Allocator;
const BinaryTree = root.BinaryTree;
const Node = root.Node;
const BTT = usize;
const TraversalContext = root.TraversalContext;
const ZigZagContext = TraversalContext(struct { data: BTT, level: usize });

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator: Allocator = gpa.allocator();

    var binaryTree = BinaryTree(BTT).init(allocator);
    defer binaryTree.deinit();

    var binaryTreeTwo = BinaryTree(BTT).init(allocator);
    defer binaryTreeTwo.deinit();

    // for (1..16) |i| try binaryTree.insert(i);
    // for (1..16) |i| try binaryTreeTwo.insert(i);

    // 1 2 2 3 4 4 3
    for ([_]BTT{ 1, 2, 2, 3, 4, 4, 3, 5 }) |value| try binaryTree.insert(value);

    //  1 2 2 0 3 0 3

    // height of the binary tree;
    // std.debug.print("height of tree : {d}\n", .{binaryTree.height()});
    // check if binary tree is balanced or not
    // std.debug.print("{}\n", .{binaryTree.isBalanced()});
    //
    // std.debug.print("{}\n", .{binaryTree.maxDiameter()});
    // std.debug.prin var queue = try Deque(struct { node: *NodeT, x: i32 }).initCapacity(self.allocator, 0);
    if (binaryTree.identical(&binaryTreeTwo))
        std.debug.print("Two tree are identical\n", .{})
    else
        std.debug.print("Two tree are not identical\n", .{});

    // zig zag with context
    // var zigZagCtx = try ZigZagContext.init(allocator);
    // defer zigZagCtx.deinit();
    // try binaryTree.zigZagCtx(&zigZagCtx, zigZagVisitCtx, false);
    // for (zigZagCtx.list.items) |item| std.debug.print("{d}:{d} | ", .{ item.data, item.level });

    // boundary traversal with context
    // std.debug.print("\n\nBoundary Traversal\n", .{});
    // try binaryTree.boundaryTraversal({}, boundaryVisit, .ANTICLOCK);

    // std.debug.print("\n\nVertical Traversal\n", .{});
    // try binaryTree.verticalTraversal({}, verticalTraversalCtx);

    // std.debug.print("\n\nTop View Traversal\n", .{});
    // try binaryTree.topView({}, topViewTraversalCtx);

    // std.debug.print("\n\nBottom View Traversal\n", .{});
    // try binaryTree.bottomView({}, topViewTraversalCtx);

    // std.debug.print("\n\nSide View Traversal\n", .{});
    // try binaryTree.sideView({}, sideViewTraversalCtx, .LEFT);

    std.debug.print("\nSymmetrical Tree\n", .{});
    const symmetrical = binaryTree.symmetrical();
    if (symmetrical)
        std.debug.print("Tree is Symmetrical", .{})
    else
        std.debug.print("Tree is not Symmetrical", .{});
}

fn zigZagVisit(data: BTT, level: usize) void {
    std.debug.print("{d}:{d}\t | ", .{ data, level });
}

fn zigZagVisitCtx(ctx: *ZigZagContext, data: BTT, level: usize) !void {
    try ctx.append(.{ .data = data, .level = level });
}

fn boundaryVisit(_: void, data: BTT) !void {
    std.debug.print("{d} ", .{data});
}

fn verticalTraversalCtx(_: void, data: BTT, vertical: i32, level: usize) !void {
    std.debug.print("Node : {d} , vertical : {d}, level : {d}\n", .{ data, vertical, level });
}

fn topViewTraversalCtx(_: void, data: BTT, vertical: i32) !void {
    std.debug.print("Node : {d} , vertical : {d}\n", .{ data, vertical });
}

fn sideViewTraversalCtx(_: void, data: BTT, level: usize) !void {
    std.debug.print("Node : {d} , level: {d}\n", .{ data, level });
}
