const std = @import("std");
const root = @import("core");

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

    var binaryTree = try BinaryTree(BTT).init(allocator);
    defer binaryTree.deinit();

    for (1..16) |i| try binaryTree.insertQueue(i);
    // for (1..16) |i| try binaryTreeTwo.insert(i);

    // 1 2 2 3 4 4 3
    // for ([_]BTT{ 1 2 2 3 4 4 3 }) |value| try binaryTree.insert(value);

    // height of the binary tree;
    // std.debug.print("height of tree : {d}\n", .{binaryTree.height()});
    // check if binary tree is balanced or not
    // std.debug.print("{}\n", .{binaryTree.isBalanced()});
    //
    // std.debug.print("{}\n", .{binaryTree.maxDiameter()});
    // std.debug.prin var queue = try Deque(struct { node: *NodeT, x: i32 }).initCapacity(self.allocator, 0);

    // check if identical
    // if (binaryTree.identical(&binaryTreeTwo))
    //     std.debug.print("Two tree are identical\n", .{})
    // else
    //     std.debug.print("Two tree are not identical\n", .{});

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

    // std.debug.print("\nSymmetrical Tree\n", .{});
    // const symmetrical = binaryTree.symmetrical();
    // if (symmetrical)
    //     std.debug.print("Tree is Symmetrical", .{})
    // else
    //     std.debug.print("Tree is not Symmetrical", .{});

    // root to node path
    // try binaryTree.rootToNode({}, boundaryVisit, 16);

    // const lca = binaryTree.LowestCommonAncestor(10, 15);
    // std.debug.print("\nLCA : {d}\n", .{lca.?});

    // const maxWidth = try binaryTree.MaxWidth();
    // std.debug.print("\nMax Widht : {d}\n", .{maxWidth});

    // binaryTree.ChildrenSum();
    // try binaryTree.levelOrder(levelOrderVisit);

    // try binaryTree.DistanceK({}, boundaryVisit, 5, 3);
    // const time = try binaryTree.BurnTreeTime(1);
    // std.debug.print("{d}\n", .{time});

    // const count = binaryTree.CountTree();
    // std.debug.print("Number of nodes : {d}\n", .{count});
    // std.debug.print("start counting\n", .{});
    // const countComplete = binaryTree.CountCompleteTree();
    // std.debug.print("Number of nodes : {d}\n", .{countComplete});
    // -----------------------------0  1   2   3  4
    // const inorder = [_]BTT{ 9, 3, 15, 20, 7 };
    // ------------------------------0  1   2   3  4
    // const preorder = [_]BTT{ 3, 9, 20, 15, 7 };

    // var binaryTreeThree = try BinaryTree(BTT).init(allocator);
    // defer binaryTreeThree.deinit();

    // try binaryTreeThree.ConstructPreorderInorder(inorder[0..], preorder[0..]);
    // try binaryTreeThree.levelOrder(levelOrderVisit);

    // try serialize(allocator);
    // try deserialize(allocator);

    // try binaryTree.MorisInorder({}, boundaryVisit);
    // std.debug.print("\n", .{});
    // try binaryTree.MorisPreorder({}, boundaryVisit);

    try binaryTree.Flatten();

    var node = binaryTree.root;
    while (node) |n| : (node = n.right) std.debug.print("{d} -> ", .{n.data});
}

fn levelOrderVisit(data: BTT, level: usize) void {
    std.debug.print("({d},{d}), ", .{ data, level });
}

fn zigZagVisitCtx(ctx: *ZigZagContext, data: BTT, level: usize) !void {
    try ctx.append(.{ .data = data, .level = level });
}

fn boundaryVisit(_: void, data: BTT) !void {
    std.debug.print("{d} -> ", .{data});
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
fn serialize(allocator: Allocator) !void {
    const SerializeBTT = usize;

    var buffer: [4096]u8 = undefined;
    const w_file = try std.fs.openFileAbsolute("/home/sachinaralapura/development/c_cpp/tuf/12-binary-tree/pp", .{
        .mode = .read_write,
    });
    defer w_file.close();

    var file_writer = w_file.writer(&buffer);
    const writer = &file_writer.interface;

    var binaryTreeThree = try BinaryTree(SerializeBTT).init(allocator);
    defer binaryTreeThree.deinit();

    const values = [_]SerializeBTT{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    for (values) |value| try binaryTreeThree.insertQueue(value);

    try binaryTreeThree.serialize(writer);
}
fn deserialize(allocator: Allocator) !void {
    var buffer: [4096]u8 = undefined;
    var threaded = std.Io.Threaded.init(allocator);
    defer threaded.deinit();

    const io = threaded.io();

    const r_file = try std.fs.openFileAbsolute("/home/sachinaralapura/development/c_cpp/tuf/12-binary-tree/pp", .{ .mode = .read_write });
    defer r_file.close();

    var file_reader = r_file.reader(io, &buffer);
    const reader = &file_reader.interface;

    var binaryTreeThree = try BinaryTree(BTT).init(allocator);
    defer binaryTreeThree.deinit();

    try binaryTreeThree.deserialize(reader);
    try binaryTreeThree.levelOrder(levelOrderVisit);
}
