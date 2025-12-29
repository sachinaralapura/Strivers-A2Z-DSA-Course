pub const std = @import("std");
pub const Allocator = std.mem.Allocator;
pub const ArrayList = std.ArrayList;
pub const Writer = std.Io.Writer;
pub const OrderT = enum(u8) { In, Pre, Post };

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
                if (current.left) |l| {
                    try queue.append(self.allocator, l);
                } else {
                    current.left = new_node;
                    return;
                }

                if (current.right) |r| {
                    try queue.append(self.allocator, r);
                } else {
                    current.right = new_node;
                    return;
                }
            }
        }

        pub fn preOrderIterCtx(self: *Self, ctx: anytype, visit: fn (@TypeOf(ctx), data: T) anyerror!void) !void {
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
        pub fn preOrderIter(self: *Self, visit: fn (data: T) void) !void {
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
        pub fn preOrderRecursive(self: *Self, visit: fn (data: T) void) void {
            preorderNode(self.root, visit);
        }
        fn preorderNode(node: ?*NodeT, visit: fn (data: T) void) void {
            if (node) |n| {
                visit(n.data);
                preorderNode(n.left, visit);
                preorderNode(n.right, visit);
            } else {
                return;
            }
        }

        pub fn inOrderIterCtx(self: *Self, ctx: anytype, visit: fn (@TypeOf(ctx), data: T) anyerror!void) !void {
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
        pub fn inOrderIter(self: *Self, visit: fn (data: T) void) !void {
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
        pub fn inOrderRecursive(self: *Self, visit: fn (data: T) void) void {
            inOrderNode(self.root, visit);
        }
        fn inOrderNode(node: ?*NodeT, visit: fn (data: T) void) void {
            if (node) |n| {
                inOrderNode(n.left, visit);
                visit(n.data);
                inOrderNode(n.right, visit);
            } else {
                return;
            }
        }

        pub fn postOrderIter(self: *Self, visit: fn (data: T) void) !void {
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
        pub fn postOrderIterCtx(self: *Self, ctx: anytype, visit: fn (@TypeOf(ctx), data: T) anyerror!void) !void {
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
        pub fn postOrderRecursive(self: *Self, visit: fn (data: T) void) void {
            postOrderNode(self.root, visit);
        }
        fn postOrderNode(node: ?*NodeT, visit: fn (data: T) void) void {
            if (node) |n| {
                postOrderNode(n.left, visit);
                postOrderNode(n.right, visit);
                visit(n.data);
            } else {
                return;
            }
        }

        pub fn traveralAllCtx(self: *Self, ctx: anytype, visit: fn (@TypeOf(ctx), data: T, order: OrderT) anyerror!void) !void {
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

        pub fn traveralAll(self: *Self, visit: fn (data: T, order: OrderT) void) !void {
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

        pub fn levelOrder(self: *Self, visit: fn (data: T) void) !void {
            var queue = try ArrayList(*NodeT).initCapacity(self.allocator, 0);
            defer queue.deinit(self.allocator);
            try queue.append(self.allocator, self.root.?);
            while (queue.items.len > 0) {
                const current = queue.orderedRemove(0);
                visit(current.data);
                if (current.left) |l| try queue.append(self.allocator, l);
                if (current.right) |r| try queue.append(self.allocator, r);
            }
        }

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

        pub fn isBalanced(self: *Self) bool {
            // return isBalancedTree(self.root.?);
            return isBalancedOpt(self.root.?).bal;
        }
        fn isBalancedOpt(node: ?*NodeT) struct {
            height: usize,
            bal: bool = true,
        } {
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
        pub fn maxDiameter(self: *Self) usize {
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
