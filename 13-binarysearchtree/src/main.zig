const std = @import("std");
const core = @import("core");
const BST = core.BinarySearchTree;

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();

    const allocator = gpa.allocator();

    var bst = BST(i32, null).init(allocator);
    defer bst.deinit();

    for ([_]usize{ 5, 3, 7, 2, 4, 6, 9, 1, 8, 10 }) |i| try bst.insert(@intCast(i));

    // const max = bst.search(10);
    // if (max) |m| std.debug.print("{f}\n", .{m});

    // const kth = bst.KthLargest(10);
    // if (kth) |k| std.debug.print("kth : {d}\n", .{k});

    // const valid = bst.ValidBST(null);
    // std.debug.print("valid bst {}\n", .{valid});
    {
        // const a = 1;
        // const b = 4;
        // const lca = bst.lowestCommonAncestor(1, 4);
        // if (lca) |l| std.debug.print("lca of {d}, {d} is {d}\n", .{ a, b, l });
    }

    {
        // const preorder = [_]i32{ 8, 5, 1, 7, 10, 12 };
        // var constructbst = BST(i32, null).init(allocator);
        // defer constructbst.deinit();
        // try constructbst.ConstructBst(preorder[0..], null);
    }
    {
        // const a = 1;
        // const suc = bst.Predecessor(8);
        // if (suc) |s| std.debug.print("Successor of {d} is {d}\n", .{ a, s });
        // try bst.Inorder({}, order);
    }
    {
        // var iterator = try bst.iterator(.DESC);
        // defer iterator.deinit();
        // while (try iterator.next()) |it| std.debug.print("{d}\n", .{it});
    }

    {
        // var three = bst.search(3);
        // var six = bst.search(6);

        // const temp = three.?.data;
        // three.?.data = six.?.data;
        // six.?.data = temp;
        // std.debug.print("Before swapping \n", .{});
        // try bst.Inorder({}, order);
        // std.debug.print("\n", .{});

        // std.debug.print("After swapping \n", .{});
        // try bst.recoverBst();
        // try bst.Inorder({}, order);
        // std.debug.print("\n", .{});
    }
}

// fn order(_: void, data: *const i32) !void {
//     std.debug.print("{d}, ", .{data.*});
// }

// fn twoSum(arr: []const i32, k: i32) bool {
//     var left: usize = 0;
//     var right = arr.len - 1;

//     while (left < right) {
//         const sum = arr[left] + arr[right];
//         if (sum == k) return true else if (sum > k) right -= 1 else left += 1;
//     }
//     return false;
// }
