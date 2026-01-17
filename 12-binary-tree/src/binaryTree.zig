pub const std = @import("std");
pub const common = @import("common.zig");

pub const Allocator = std.mem.Allocator;
pub const ArrayList = std.ArrayList;
pub const Deque = std.Deque;
pub const HashMap = std.AutoHashMap;
pub const Writer = std.Io.Writer;
pub const OrderT = enum(u8) { In, Pre, Post };
pub const IsNumber = common.isNumber;

pub fn Node(comptime T: type) type {
    return struct {
        const Self = @This();
        data: T,
        left: ?*Self = null,
        right: ?*Self = null,

        pub fn init(allocator: Allocator, data: T) !*Self {
            const ptr = try allocator.create(Self);
            ptr.* = .{
                .data = data,
                .left = null,
                .right = null,
            };
            return ptr;
        }

        pub fn deinit(self: *Self, allocator: Allocator) void {
            if (self.left) |l| l.deinit(allocator);
            if (self.right) |r| r.deinit(allocator);
            allocator.destroy(self);
        }

        pub fn format(self: Self, writer: *Writer) Writer.Error!void {
            try writer.print("{}", .{self.data});
        }
    };
}

pub fn BinaryTree(comptime T: type) type {
    return struct {
        const Self = @This();
        const NodeT = Node(T);

        root: ?*NodeT,
        allocator: Allocator,

        pub fn init(allocator: Allocator) Self {
            return .{
                .root = null,
                .allocator = allocator,
            };
        }
        pub fn initRoot(allocator: Allocator, root: ?*NodeT) Self {
            return .{
                .root = root,
                .allocator = allocator,
            };
        }
        pub fn deinit(self: *Self) void {
            if (self.root) |r| r.deinit(self.allocator);
        }

        pub fn insert(self: *Self, data: T) !void {
            const new_node = try NodeT.init(self.allocator, data);

            if (self.root == null) {
                self.root = new_node;
                return;
            }
            var queue = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.append(self.allocator, self.root.?);

            while (queue.items.len > 0) {
                const current = queue.orderedRemove(0);
                if (current.left) |l| try queue.append(self.allocator, l) else {
                    current.left = new_node;
                    return;
                }

                if (current.right) |r| try queue.append(self.allocator, r) else {
                    current.right = new_node;
                    return;
                }
            }
        }

        pub fn preOrderIterCtx(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
        ) !void {
            if (self.root == null) return;
            var stack = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer stack.deinit(self.allocator);

            try stack.append(self.allocator, self.root.?);

            while (stack.items.len > 0) {
                const node = stack.pop();
                if (node) |n| {
                    try visit(ctx, n.data);
                    if (n.right) |r| try stack.append(self.allocator, r);
                    if (n.left) |l| try stack.append(self.allocator, l);
                }
            }
        }
        pub fn preOrderIter(
            self: *Self,
            visit: fn (data: T) void,
        ) !void {
            if (self.root == null) return;
            var stack = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer stack.deinit(self.allocator);

            try stack.append(self.allocator, self.root.?);

            while (stack.items.len > 0) {
                const node = stack.pop();
                if (node) |n| {
                    visit(n.data);
                    if (n.right) |r| try stack.append(self.allocator, r);
                    if (n.left) |l| try stack.append(self.allocator, l);
                }
            }
        }
        pub fn preOrderRecursive(
            self: *Self,
            visit: fn (data: T) void,
        ) void {
            preorderNode(self.root, visit);
        }
        fn preorderNode(node: ?*NodeT, visit: fn (data: T) void) void {
            if (node) |n| {
                visit(n.data);
                preorderNode(n.left, visit);
                preorderNode(n.right, visit);
            } else return;
        }

        pub fn inOrderIterCtx(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
        ) !void {
            var stack = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer stack.deinit(self.allocator);
            var current = self.root;
            while (current != null or stack.items.len > 0) {
                while (current) |node| {
                    try stack.append(self.allocator, node);
                    current = node.left;
                }
                const node = stack.pop();
                if (node) |n| {
                    visit(ctx, n.data);
                    current = n.right;
                }
            }
        }
        pub fn inOrderIter(
            self: *Self,
            visit: fn (data: T) void,
        ) !void {
            var stack = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer stack.deinit(self.allocator);
            var current = self.root;
            while (current != null or stack.items.len > 0) {
                while (current) |node| {
                    try stack.append(self.allocator, node);
                    current = node.left;
                }
                const node = stack.pop();
                if (node) |n| {
                    visit(n.data);
                    current = n.right;
                }
            }
        }
        pub fn inOrder(
            self: *Self,
            ctx: anytype,
            comptime visit: fn (@TypeOf(ctx), data: T) void,
        ) void {
            inOrderTree(self.root, ctx, visit);
        }
        fn inOrderTree(
            node: ?*NodeT,
            ctx: anytype,
            comptime visit: fn (@TypeOf(ctx), data: T) void,
        ) void {
            if (node) |n| {
                inOrderTree(n.left, ctx, visit);
                visit(ctx, n.data);
                inOrderTree(n.right, ctx, visit);
            } else return;
        }

        pub fn postOrderIter(
            self: *Self,
            visit: fn (data: T) void,
        ) !void {
            if (self.root == null) return;
            var stack_one = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            var stack_two = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer stack_one.deinit(self.allocator);
            defer stack_two.deinit(self.allocator);
            try stack_one.append(self.allocator, self.root.?);
            while (stack_one.items.len > 0) {
                const node = stack_one.pop();
                if (node) |n| {
                    try stack_two.append(self.allocator, n);
                    if (n.left) |l| try stack_one.append(self.allocator, l);
                    if (n.right) |r| try stack_two.append(self.allocator, r);
                }
            }
            while (stack_two.pop()) |node| visit(node.data);
        }
        pub fn postOrderIterCtx(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
        ) !void {
            if (self.root == null) return;
            var stack_one = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            var stack_two = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer stack_one.deinit(self.allocator);
            defer stack_two.deinit(self.allocator);
            try stack_one.append(self.allocator, self.root.?);
            while (stack_one.items.len > 0) {
                const node = stack_one.pop();
                if (node) |n| {
                    try stack_two.append(self.allocator, n);
                    if (n.left) |l| try stack_one.append(self.allocator, l);
                    if (n.right) |r| try stack_two.append(self.allocator, r);
                }
            }
            while (stack_two.pop()) |node| visit(ctx, node.data);
        }
        pub fn postOrderRecursive(
            self: *Self,
            visit: fn (data: T) void,
        ) void {
            postOrderNode(self.root, visit);
        }
        fn postOrderNode(node: ?*NodeT, visit: fn (data: T) void) void {
            if (node) |n| {
                postOrderNode(n.left, visit);
                postOrderNode(n.right, visit);
                visit(n.data);
            } else return;
        }

        pub fn traveralAllCtx(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T, order: OrderT) anyerror!void,
        ) !void {
            var stack = try ArrayList(struct { node: *NodeT, state: OrderT }).initCapacity(self.allocator, 0);
            defer stack.deinit(self.allocator);
            try stack.append(self.allocator, .{ .node = self.root.?, .state = .Pre });
            while (stack.items.len > 0) {
                const item = &stack.items[stack.items.len - 1];
                switch (item.state) {
                    .Pre => {
                        try visit(ctx, item.node.data, .Pre);
                        item.state = .In;
                        if (item.node.left) |l|
                            try stack.append(self.allocator, .{ .node = l, .state = .Pre });
                    },
                    .In => {
                        try visit(ctx, item.node.data, .In);
                        item.state = .Post;
                        if (item.node.right) |r|
                            try stack.append(self.allocator, .{ .node = r, .state = .Pre });
                    },
                    .Post => {
                        try visit(ctx, item.node.data, .Post);
                        _ = stack.pop();
                    },
                }
            }
        }

        pub fn traveralAll(
            self: *Self,
            visit: fn (data: T, order: OrderT) void,
        ) !void {
            var stack = try ArrayList(struct { node: *NodeT, state: OrderT }).initCapacity(self.allocator, 0);
            defer stack.deinit(self.allocator);
            try stack.append(self.allocator, .{ .node = self.root.?, .state = .Pre });
            while (stack.items.len > 0) {
                const item = &stack.items[stack.items.len - 1];
                switch (item.state) {
                    .Pre => {
                        visit(item.node.data, .Pre);
                        item.state = .In;
                        if (item.node.left) |l|
                            try stack.append(self.allocator, .{ .node = l, .state = .Pre });
                    },
                    .In => {
                        visit(item.node.data, .In);
                        item.state = .Post;
                        if (item.node.right) |r|
                            try stack.append(self.allocator, .{ .node = r, .state = .Pre });
                    },
                    .Post => {
                        visit(item.node.data, .Post);
                        _ = stack.pop();
                    },
                }
            }
        }

        pub fn levelOrder(
            self: *Self,
            visit: fn (data: T, level: usize) void,
        ) !void {
            if (self.root == null) return;
            var queue = try Deque(*NodeT).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.pushBack(self.allocator, self.root.?);
            var level: usize = 0;
            while (queue.len > 0) : (level += 1) {
                const size = queue.len;
                for (0..size) |_| {
                    const current = queue.popFront();
                    if (current) |cur| {
                        visit(cur.data, level);
                        if (cur.left) |l| try queue.pushBack(self.allocator, l);
                        if (cur.right) |r| try queue.pushBack(self.allocator, r);
                    }
                }
            }
        }

        /// Given the root of a Binary Tree, return the height of the tree.
        /// The height of the tree is equal to the number of nodes on the
        /// longest path from root to a leaf.
        pub fn height(self: *Self) usize {
            if (self.root) |r| return heightNode(r);
            return 0;
        }
        fn heightNode(node: ?*NodeT) usize {
            if (node == null) return 0;
            const left_height: usize = heightNode(node.?.left);
            const right_height: usize = heightNode(node.?.right);
            return 1 + @max(left_height, right_height);
        }

        /// Given a Binary Tree, return true if it is a Balanced Binary Tree else return false.
        /// A Binary Tree is balanced if, for all nodes in the tree, the difference between
        /// left and right subtree height is not more than 1.
        pub fn isBalanced(self: *Self) bool {
            // return isBalancedTree(self.root.?);
            if (self.root == null) return true;
            return isBalancedOpt(self.root.?).bal;
        }
        fn isBalancedOpt(node: ?*NodeT) struct { height: usize, bal: bool = true } {
            if (node == null) return .{ .height = 0 };

            const l = isBalancedOpt(node.?.left);
            if (!l.bal) return .{ .bal = false, .height = 0 };

            const r = isBalancedOpt(node.?.right);
            if (!r.bal) return .{ .height = 0, .bal = false };

            if (@abs(l.height - r.height) > 1) return .{ .height = 0, .bal = false };

            return .{ .height = 1 + @max(l.height, r.height) };
        }
        fn isBalancedTree(node: ?*NodeT) bool {
            if (node == null) return true;
            const l_height = heightNode(node.?.left);
            const r_height = heightNode(node.?.right);
            if (@abs(l_height - r_height) > 1) return false;
            const l_bal = isBalancedTree(node.?.left);
            const r_bal = isBalancedTree(node.?.right);
            return l_bal and r_bal;
        }

        /// Given the root of the Binary Tree, return the length of its diameter.
        /// The Diameter of a Binary Tree is the longest distance between any
        /// two nodes of that tree. This path may or may not pass through the root.
        pub fn maxDiameter(self: *Self) usize {
            if (self.root == null) return 0;
            var diameter: usize = 0;
            _ = maxDiameterTree(&diameter, self.root.?);
            return diameter;
        }
        fn maxDiameterTree(diameter: *usize, node: ?*NodeT) usize {
            if (node == null) return 0;
            const l_height = maxDiameterTree(diameter, node.?.left);
            const r_height = maxDiameterTree(diameter, node.?.right);
            diameter.* = @max(diameter.*, l_height + r_height);
            return 1 + @max(l_height, r_height);
        }

        /// Given a Binary Tree, determine the maximum sum achievable along any path within the tree.
        /// A path in a binary tree is defined as a sequence of nodes where each pair of adjacent nodes
        /// is connected by an edge. Nodes can only appear once in the sequence, and the path is not
        /// required to start from the root.
        /// Identify and compute the maximum sum possible along any path within the given binary tree.
        pub fn maxSumPath(self: *Self) T {
            comptime if (!IsNumber(T)) @compileError("Node type should be number\n");
            var maxSum: T = 0;
            _ = maxSumPathTree(&maxSum, self.root);
            return maxSum;
        }
        fn maxSumPathTree(max: *T, node: ?*NodeT) T {
            if (node == null) return 0;
            const l_max = @max(0, maxSumPathTree(max, node.?.left));
            const r_max = @max(0, maxSumPathTree(max, node.?.right));
            max.* = @max(max.*, l_max + r_max + node.?.data);
            return @max(l_max, r_max) + node.?.data;
        }

        ///  ## Given two Binary Trees, return if true if the two trees are identical, otherwise return false..
        ///
        /// ### Two trees are said to be identical if these three conditions are met for every pair of nodes :
        ///
        ///     1. Value of a node in the first tree is equal to the value of the corresponding node in the second tree.
        ///
        ///     2. Left subtree of this node is identical to the left subtree of the corresponding node.
        ///
        ///     3. Right subtree of this node is identical to the right subtree of the corresponding node.
        pub fn identical(self: *Self, root: *Self) bool {
            if (self.root == null and root.root == null) return true;
            if (self.root == null or root.root == null) return false;
            return identicalTree(self.root.?, root.root.?);
        }
        fn identicalTree(a: ?*NodeT, b: ?*NodeT) bool {
            if (a == null and b == null) return true;
            if (a == null or b == null) return false;
            if (a.?.data != b.?.data) return false;
            const l = identicalTree(a.?.left, b.?.left);
            const r = identicalTree(a.?.right, b.?.right);
            return l and r;
        }

        /// Given a Binary Tree, print the zigzag traversal of the Binary Tree.
        /// Zigzag traversal of a binary tree is a way of visiting the nodes of
        /// the tree in a zigzag pattern, alternating between `left-to-right` and `right-to-left` at each level.
        pub fn zigZag(
            self: *Self,
            visit: fn (data: T, level: usize) void,
            direction: bool,
        ) !void {
            if (self.root == null) return;
            var flag: bool = direction;
            var queue: ArrayList(*NodeT) = try .initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.append(self.allocator, self.root.?);
            var level: usize = 0;
            while (queue.items.len > 0) : (level += 1) {
                const size = queue.items.len;
                var row = try self.allocator.alloc(T, size);
                defer self.allocator.free(row);
                for (0..size) |i| {
                    const front = queue.orderedRemove(0);
                    const index: usize = if (flag) i else (size - 1 - i);
                    row[index] = front.data;
                    if (front.left) |l| try queue.append(self.allocator, l);
                    if (front.right) |r| try queue.append(self.allocator, r);
                }
                for (row) |t| visit(t, level);
                flag = !flag;
            }
        }
        pub fn zigZagCtx(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T, level: usize) anyerror!void,
            direction: bool,
        ) !void {
            if (self.root == null) return;
            var flag: bool = direction;
            var queue: ArrayList(*NodeT) = try .initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.append(self.allocator, self.root.?);
            var level: usize = 0;
            while (queue.items.len > 0) : (level += 1) {
                const size = queue.items.len;
                var row = try self.allocator.alloc(T, size);
                defer self.allocator.free(row);
                for (0..size) |i| {
                    const front = queue.orderedRemove(0);
                    const index: usize = if (flag) i else (size - 1 - i);
                    row[index] = front.data;
                    if (front.left) |l| try queue.append(self.allocator, l);
                    if (front.right) |r| try queue.append(self.allocator, r);
                }
                for (row) |t| try visit(ctx, t, level);
                flag = !flag;
            }
        }

        /// Given a Binary Tree, perform the boundary traversal of the tree.
        /// The boundary traversal is the process of visiting the boundary nodes
        /// of the binary tree in the anticlockwise direction, starting from the root.
        pub fn boundaryTraversal(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
            direction: enum(u8) { CLOCK, ANTICLOCK },
        ) !void {
            if (self.root == null) return;
            try visit(ctx, self.root.?.data);
            switch (direction) {
                .CLOCK => try clockBoundary(self.root.?, self.allocator, ctx, visit),
                .ANTICLOCK => try antiClockBoundary(self.root.?, self.allocator, ctx, visit),
            }
        }
        fn leafNodes(
            node: *NodeT,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
            direction: bool,
        ) !void {
            if (node.left == null and node.right == null) {
                try visit(ctx, node.data);
                return;
            }
            if (direction) {
                if (node.left) |l| try leafNodes(l, ctx, visit, direction);
                if (node.right) |r| try leafNodes(r, ctx, visit, direction);
            } else {
                if (node.right) |r| try leafNodes(r, ctx, visit, direction);
                if (node.left) |l| try leafNodes(l, ctx, visit, direction);
            }
        }
        fn clockBoundary(
            root: *NodeT,
            allocator: Allocator,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
        ) !void {
            // visit left boundary nodes
            var node = root.left;
            while (node) |n| {
                if (n.left != null or n.right != null) try visit(ctx, n.data);
                if (n.left) |l| node = l else node = n.right;
            }
            // visit leaf nodes
            try leafNodes(root, ctx, visit, true);
            // visit right boundary nodes
            if (root.right == null) return;
            node = root.right;
            var temp = try ArrayList(*NodeT).initCapacity(allocator, 5);
            defer temp.deinit(allocator);
            while (node) |n| {
                if (n.left != null or n.right != null) try temp.append(allocator, n);
                if (n.right) |r| node = r else node = n.left;
            }
            while (temp.pop()) |n| try visit(ctx, n.data);
        }
        fn antiClockBoundary(
            root: *NodeT,
            allocator: Allocator,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
        ) !void {
            // visit right boundary nodes
            var node = root.right;
            while (node) |n| {
                if (n.right != null or n.left != null) try visit(ctx, n.data);
                if (n.right) |r| node = r else node = n.right;
            }
            // visit leaft nodes
            try leafNodes(root, ctx, visit, false);
            // visit left boundary nodes
            if (root.left == null) return;
            node = root.left;
            var temp = try ArrayList(*NodeT).initCapacity(allocator, 5);
            defer temp.deinit(allocator);
            while (node) |n| {
                if (n.left != null or n.right != null) try temp.append(allocator, n);
                if (n.left) |r| node = r else node = n.right;
            }
            while (temp.pop()) |n| try visit(ctx, n.data);
        }

        /// Given a Binary Tree, return the Vertical Order Traversal of it starting from the
        /// Leftmost level to the Rightmost level. If there are multiple nodes passing through a
        /// vertical line, then they should be printed as they appear in level order traversal of the tree.
        pub fn verticalTraversal(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T, vertical: i32, level: usize) anyerror!void,
        ) !void {
            if (self.root == null) return;
            var queue = try Deque(struct { node: *NodeT, x: i32, y: usize }).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.pushBack(self.allocator, .{ .y = 0, .x = 0, .node = self.root.? });
            while (queue.len > 0) {
                const current = queue.popFront();
                if (current) |cur| {
                    try visit(ctx, cur.node.data, cur.x, cur.y);

                    if (cur.node.right) |r|
                        try queue.pushBack(self.allocator, .{ .node = r, .x = cur.x + 1, .y = cur.y + 1 });

                    if (cur.node.left) |l|
                        try queue.pushBack(self.allocator, .{ .node = l, .x = cur.x - 1, .y = cur.y + 1 });
                }
            }
        }

        /// Given a Binary Tree, return its Top View.
        /// The Top View of a Binary Tree is the set of nodes visible when we see the tree from the top.
        pub fn topView(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T, vertical: i32) anyerror!void,
        ) !void {
            if (self.root == null) return;
            var queue = try Deque(struct { node: *NodeT, x: i32 }).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.pushBack(self.allocator, .{ .node = self.root.?, .x = 0 });

            var right: i32 = -1;
            var left: i32 = 1;
            while (queue.len > 0) {
                const current = queue.popFront();
                if (current) |cur| {
                    if (cur.x > right or cur.x < left) {
                        try visit(ctx, cur.node.data, cur.x);
                        right = @max(right, cur.x);
                        left = @min(left, cur.x);
                    }
                    if (cur.node.left) |l|
                        try queue.pushBack(self.allocator, .{ .node = l, .x = cur.x - 1 });

                    if (cur.node.right) |r|
                        try queue.pushBack(self.allocator, .{ .node = r, .x = cur.x + 1 });
                }
            }
        }

        /// Given a Binary Tree, return its Bottom View.
        /// The Bottom View of a Binary Tree is the set of nodes visible when we see the tree from the bottom.
        pub fn bottomView(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T, vertical: i32) anyerror!void,
        ) !void {
            if (self.root == null) return;
            var queue = try Deque(struct { node: *NodeT, x: i32 }).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);

            var map = HashMap(i32, *NodeT).init(self.allocator);
            defer map.deinit();
            try queue.pushBack(self.allocator, .{ .node = self.root.?, .x = 0 });
            while (queue.len > 0) {
                const current = queue.popFront();
                if (current) |cur| {
                    try map.put(cur.x, cur.node);
                    if (cur.node.left) |l|
                        try queue.pushBack(self.allocator, .{ .node = l, .x = cur.x - 1 });
                    if (cur.node.right) |r|
                        try queue.pushBack(self.allocator, .{ .node = r, .x = cur.x + 1 });
                }
            }
            var iterator = map.iterator();
            while (iterator.next()) |item| try visit(ctx, item.value_ptr.*.data, item.key_ptr.*);
        }

        /// Assuming standing on the right side of a binary tree and given its root,
        /// return the values of the nodes visible, arranged from top to bottom.
        pub fn sideView(
            self: *Self,
            ctx: anytype,
            comptime visit: fn (@TypeOf(ctx), data: T, level: usize) anyerror!void,
            side: enum(u8) { RIGHT, LEFT },
        ) !void {
            if (self.root == null) return;
            try visit(ctx, self.root.?.data, 0);
            var maxLevel: usize = 0;
            switch (side) {
                .RIGHT => try rightViewTree(self.root, ctx, visit, 0, &maxLevel),
                .LEFT => try leftViewTree(self.root, ctx, visit, 0, &maxLevel),
            }
        }

        fn rightViewTree(
            node: ?*NodeT,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T, level: usize) anyerror!void,
            level: usize,
            maxlevel: *usize,
        ) !void {
            if (node == null) return;
            if (level > maxlevel.*) {
                try visit(ctx, node.?.data, level);
                maxlevel.* = level;
            }
            if (node.?.right) |r| try rightViewTree(r, ctx, visit, level + 1, maxlevel);
            if (node.?.left) |l| try rightViewTree(l, ctx, visit, level + 1, maxlevel);
        }

        fn leftViewTree(
            node: ?*NodeT,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T, level: usize) anyerror!void,
            level: usize,
            maxlevel: *usize,
        ) !void {
            if (node == null) return;
            if (level > maxlevel.*) {
                try visit(ctx, node.?.data, level);
                maxlevel.* = level;
            }
            if (node.?.left) |l| try leftViewTree(l, ctx, visit, level + 1, maxlevel);
            if (node.?.right) |r| try leftViewTree(r, ctx, visit, level + 1, maxlevel);
        }

        /// Given a Binary Tree, determine whether the given tree is symmetric or not.
        /// A Binary Tree would be Symmetric, when its mirror image is exactly the same
        /// as the original tree. If we were to draw a vertical line through the centre of the tree,
        /// the nodes on the left and right side would be mirror images of each other.
        pub fn symmetrical(self: *Self) bool {
            if (self.root) |root| return symmetricalTree(root.left, root.right) else return true;
        }
        fn symmetricalTree(a: ?*NodeT, b: ?*NodeT) bool {
            if (a == null and b == null) return true;
            if (a == null or b == null) return false;
            if (a.?.data != b.?.data) return false;
            const l = symmetricalTree(a.?.left, b.?.left);
            const r = symmetricalTree(a.?.right, b.?.right);
            return l and r;
        }

        /// Given a Binary Tree and a reference to a root belonging to it.
        /// Return the path from the root node to the given leaf node.
        pub fn rootToNode(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
            x: T,
        ) !void {
            if (self.root == null) return;

            var list = try ArrayList(T).initCapacity(self.allocator, 0);
            defer list.deinit(self.allocator);

            _ = try rootToNodePath(self.root, &list, x, self.allocator);
            for (list.items) |it| try visit(ctx, it);
        }
        fn rootToNodePath(
            node: ?*NodeT,
            list: *ArrayList(T),
            x: T,
            a: Allocator,
        ) !bool {
            if (node) |n| {
                _ = try list.append(a, n.data);
                if (n.data == x) return true;

                const left = try rootToNodePath(n.left, list, x, a);
                if (left) return true;

                const right = try rootToNodePath(n.right, list, x, a);
                if (right) return true;

                _ = list.pop();
                return false;
            } else return false;
        }

        /// Given a root of binary tree, find the lowest common ancestor (LCA)
        /// of two given nodes (p, q) in the tree.
        /// The lowest common ancestor is defined between two nodes p and q
        /// as the lowest node in T that has both p and q as descendants
        /// (where we allow a node to be a descendant of itself).
        pub fn LowestCommonAncestor(self: *Self, a: T, b: T) ?T {
            if (self.root == null) return null;
            return lca(self.root, a, b);
        }
        fn lca(node: ?*NodeT, a: T, b: T) ?T {
            if (node) |n| {
                if (n.data == a) return a;
                if (n.data == b) return b;

                const left = lca(n.left, a, b);
                const right = lca(n.right, a, b);

                if (left != null and right != null) return n.data;
                if (left) |l| return l;
                if (right) |r| return r;

                return null;
            } else return null;
        }

        /// Given a Binary Tree, return its maximum width.
        /// The maximum width of a Binary Tree is the maximum diameter among all its levels.
        /// The width or diameter of a level is the number of nodes between the leftmost and rightmost nodes.
        pub fn MaxWidth(self: *Self) !usize {
            if (self.root == null) return 0;
            var queue = try Deque(struct { node: *NodeT, min: usize }).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.pushBack(self.allocator, .{ .node = self.root.?, .min = 0 });
            var maxWidth: usize = 0;
            while (queue.len > 0) {
                const size = queue.len;
                const mmin = queue.front().?.min;
                var first: usize = 0;
                var last: usize = 0;
                for (0..size) |i| {
                    const cur_id = queue.front().?.min - mmin;
                    const node = queue.front().?.node;
                    _ = queue.popFront();
                    if (i == 0) first = cur_id;
                    if (i == size - 1) last = cur_id;

                    if (node.left) |l| try queue.pushBack(self.allocator, .{ .node = l, .min = cur_id * 2 + 1 });
                    if (node.right) |r| try queue.pushBack(self.allocator, .{ .node = r, .min = cur_id * 2 + 2 });
                }
                maxWidth = @max(maxWidth, last - first + 1);
            }
            return maxWidth;
        }

        /// Given a Binary Tree, convert the value of its nodes to follow the Children Sum Property. The Children Sum Property in a binary tree states that for every node, the sum of its children's values (if they exist) should be equal to the node's value. If a child is missing, it is considered as having a value of 0.
        /// ### Note:
        ///   -  The node values can be increased by any positive integer any number of times, but decrementing any node value is not allowed.
        ///   -  A value for a NULL node can be assumed as 0.
        ///   -  We cannot change the structure of the given binary tree.
        pub fn ChildrenSum(self: *Self) void {
            if (self.root == null) return;
            comptime if (!IsNumber(T)) @compileError("Node type should be number\n");
            childrenSumNode(self.root);
        }
        fn childrenSumNode(node: ?*NodeT) void {
            if (node) |n| {
                var child: T = 0;
                if (n.left) |l| child += l.data;
                if (n.right) |r| child += r.data;

                if (child >= n.data) n.data = child else {
                    if (n.left) |l| l.data = n.data;
                    if (n.right) |r| r.data = n.data;
                }

                childrenSumNode(n.left);
                childrenSumNode(n.right);

                var total: T = 0;
                if (n.left) |l| total += l.data;
                if (n.right) |r| total += r.data;
                if (n.left != null or n.right != null) n.data = total; // if not leaf;
            }
        }

        /// Given the root of a binary tree, the value of a target node target,
        /// and an integer k. Return an array of the values of all nodes that
        /// have a distance k from the target node. The answer can be returned in any order (N represents null).
        pub fn DistanceK(
            self: *Self,
            ctx: anytype,
            visit: fn (@TypeOf(ctx), data: T) anyerror!void,
            x: T,
            k: usize,
        ) !void {
            if (self.root == null) return;
            var parentMap = HashMap(*NodeT, *NodeT).init(self.allocator);
            defer parentMap.deinit();

            try self.buildParentMap(&parentMap);

            const node = try self.findNode(x, self.root);
            if (node == null) return;

            var queue = try Deque(*NodeT).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.pushBack(self.allocator, node.?);

            var visited = HashMap(*NodeT, void).init(self.allocator);
            defer visited.deinit();
            try visited.put(node.?, {});

            var distance: usize = 0;

            while (queue.len > 0) {
                const size = queue.len;
                if (distance == k) break;
                distance += 1;

                for (0..size) |_| {
                    const current = queue.popFront();
                    if (current) |curr| {
                        if (curr.left) |l| {
                            if (!visited.contains(l)) {
                                try visited.put(l, {});
                                try queue.pushBack(self.allocator, l);
                            }
                        }

                        if (curr.right) |r| {
                            if (!visited.contains(r)) {
                                try visited.put(r, {});
                                try queue.pushBack(self.allocator, r);
                            }
                        }

                        if (parentMap.get(curr)) |n| {
                            if (!visited.contains(n)) {
                                try visited.put(n, {});
                                try queue.pushBack(self.allocator, n);
                            }
                        }
                    }
                }
            }
            while (queue.popBack()) |n| try visit(ctx, n.data);
        }
        fn buildParentMap(
            self: *Self,
            parentMap: *HashMap(*NodeT, *NodeT),
        ) !void {
            if (self.root == null) return;
            var queue = try Deque(*NodeT).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.pushBack(self.allocator, self.root.?);

            while (queue.len > 0) {
                const size = queue.len;
                for (0..size) |_| {
                    const current = queue.popFront();
                    if (current) |cur| {
                        if (cur.left) |l| {
                            try parentMap.put(l, cur);
                            try queue.pushBack(self.allocator, l);
                        }
                        if (cur.right) |r| {
                            try parentMap.put(r, cur);
                            try queue.pushBack(self.allocator, r);
                        }
                    }
                }
            }
        }
        fn findNode(
            self: *Self,
            x: T,
            node: ?*NodeT,
        ) !?*NodeT {
            if (node) |n| {
                if (n.data == x) return n;

                const left = try self.findNode(x, n.left);
                if (left) |l| return l;

                const right = try self.findNode(x, n.right);
                if (right) |r| return r;

                return null;
            } else return null;
        }

        /// Given a target node data and a root of binary tree. If the target is set on fire,
        /// determine the shortest amount of time needed to burn the entire binary tree.
        /// It is known that in 1 second all nodes connected to a given node get burned.
        /// That is its left child, right child, and parent.
        pub fn BurnTreeTime(self: *Self, x: T) !usize {
            if (self.root == null) return 0;
            var parentMap = HashMap(*NodeT, *NodeT).init(self.allocator);
            defer parentMap.deinit();

            try self.buildParentMap(&parentMap);

            const node = try self.findNode(x, self.root);
            if (node == null) return 0;

            var queue = try Deque(*NodeT).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.pushBack(self.allocator, node.?);

            var visited = HashMap(*NodeT, void).init(self.allocator);
            defer visited.deinit();
            try visited.put(node.?, {});

            var time: usize = 0;

            while (queue.len > 0) {
                const size = queue.len;
                for (0..size) |_| {
                    const current = queue.popFront();
                    if (current) |curr| {
                        if (curr.left) |l| {
                            if (!visited.contains(l)) {
                                try visited.put(l, {});
                                try queue.pushBack(self.allocator, l);
                            }
                        }

                        if (curr.right) |r| {
                            if (!visited.contains(r)) {
                                try visited.put(r, {});
                                try queue.pushBack(self.allocator, r);
                            }
                        }

                        if (parentMap.get(curr)) |n| {
                            if (!visited.contains(n)) {
                                try visited.put(n, {});
                                try queue.pushBack(self.allocator, n);
                            }
                        }
                    }
                }
                time += 1;
            }
            return time;
        }

        // Given a Complete Binary Tree, count and return the number of nodes in the given tree.
        // A Complete Binary Tree is a binary tree in which all levels are completely filled,
        // except possibly for the last level, and all nodes are as left as possible.
        pub fn CountTree(self: *Self) usize {
            if (self.root == null) return 0;
            var count: usize = 0;
            inOrderTree(self.root.?, &count, countTreeContext);
            return count;
        }
        fn countTreeContext(ctx: *usize, _: T) void {
            ctx.* = ctx.* + 1;
        }
    };
}

pub fn TraversalAllContext(comptime T: type) type {
    return struct {
        const Self = @This();

        Pre: ArrayList(T),
        In: ArrayList(T),
        Post: ArrayList(T),
        allocator: Allocator,
        pub fn init(alloctor: Allocator) !Self {
            return .{
                .allocator = alloctor,
                .Pre = try ArrayList(T).initCapacity(alloctor, 0),
                .In = try ArrayList(T).initCapacity(alloctor, 0),
                .Post = try ArrayList(T).initCapacity(alloctor, 0),
            };
        }
        pub fn deinit(self: *Self) void {
            self.Pre.deinit(self.allocator);
            self.In.deinit(self.allocator);
            self.Post.deinit(self.allocator);
        }
        pub fn PreOrder(self: *Self, data: T) !void {
            try self.Pre.append(self.allocator, data);
        }
        pub fn InOrder(self: *Self, data: T) !void {
            try self.In.append(self.allocator, data);
        }
        pub fn PostOrder(self: *Self, data: T) !void {
            try self.Post.append(self.allocator, data);
        }
    };
}

pub fn TraversalContext(comptime T: type) type {
    return struct {
        const Self = @This();
        list: ArrayList(T),
        allocator: Allocator,
        pub fn init(alloctor: Allocator) !Self {
            return .{
                .allocator = alloctor,
                .list = try ArrayList(T).initCapacity(alloctor, 0),
            };
        }
        pub fn deinit(self: *Self) void {
            self.list.deinit(self.allocator);
        }
        pub fn append(self: *Self, data: T) !void {
            try self.list.append(self.allocator, data);
        }
    };
}
