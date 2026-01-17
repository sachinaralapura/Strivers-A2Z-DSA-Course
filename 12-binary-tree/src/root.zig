const std = @import("std");

const Bt = @import("binaryTree.zig");

pub const BinaryTree = Bt.BinaryTree;
pub const Node = Bt.Node;
pub const OrderBt = Bt.OrderT;
pub const TraverseAllCtx = Bt.TraversalAllContext;
pub const TraversalContext = Bt.TraversalContext;

pub const common = @import("common.zig");
pub const Add = common.add;
pub const IsNumber = common.isNumber;

// pub fn add(comptime T: type) void {
//     if (!IsNumber(T)) {
//         std.debug.print("Should be number\n", .{});
//     } else {
//         std.debug.print("Is a number\n", .{});
//     }
// }
// pub fn main() !void {
//     const pp: ?usize = null;
//     std.debug.print("{d}", .{pp.?});
// }
