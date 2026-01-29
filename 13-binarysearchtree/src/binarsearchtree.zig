const std = @import("std");
const Allocator = std.mem.Allocator;
const Deque = std.Deque;

const Writer = std.Io.Writer;
const Reader = std.Io.Reader;

fn defautltComp(comptime T: type) ?fn (a: T, b: T) i8 {
    const gen = struct {
        pub fn compare(a: T, b: T) i8 {
            if (a < b) return -1 else if (a > b) return 1 else return 0;
        }
    };
    const node_type = @typeInfo(T);
    return switch (node_type) {
        .int, .float => gen.compare,
        else => null,
    };
}

pub fn Node(comptime T: type, com: ?fn (a: T, b: T) i8) type {
    return struct {
        const Self = @This();
        data: T,
        left: ?*Self = null,
        right: ?*Self = null,

        // if a compare function is provided, use it
        // else if T has a default compare function, use that
        // else leave it undefined
        /// if a == b return 0
        /// if a < b return -1
        /// if a > b return 1
        pub var compare: *const fn (a: T, b: T) i8 = if (com) |cmp| &cmp else if (defautltComp(T)) |cmp| &cmp else undefined;

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
            // std.debug.print("{d}, ", .{self.data});
            if (self.left) |l| l.deinit(allocator);
            if (self.right) |r| r.deinit(allocator);
            allocator.destroy(self);
        }

        pub fn format(self: Self, writer: *Writer) Writer.Error!void {
            try writer.print("{}", .{self.data});
        }

        pub fn lt(self: *Self, other: *Self) bool {
            if (compare(self.data, other.data) == -1) return true;
            return false;
        }
        pub fn ltd(self: *Self, data: T) bool {
            if (compare(self.data, data) == -1) return true;
            return false;
        }

        pub fn eqt(self: *Self, other: *Self) bool {
            if (compare(self.data, other.data) == 0) return true;
            return false;
        }
        pub fn eqtd(self: *Self, data: T) bool {
            if (compare(self.data, data) == 0) return true;
            return false;
        }

        pub fn gt(self: *Self, other: *Self) bool {
            if (compare(self.data, other.data) == 1) return true;
            return false;
        }
        pub fn gtd(self: *Self, data: T) bool {
            if (compare(self.data, data) == 1) return true;
            return false;
        }
    };
}

pub fn BinarySearchTree(comptime T: type, lessThanFn: ?fn (a: T, b: T) i8) type {
    return struct {
        const Self = @This();
        const NodeT = Node(T, lessThanFn);
        const Range = struct { left: T, right: T };

        const Iterator = struct {
            const Order = enum(u8) { ASC, DESC };

            allocator: Allocator,
            stack: Deque(*NodeT),
            bst: *BinarySearchTree(T, lessThanFn),
            /// don't change
            order: Order,

            pub fn init(
                allocator: Allocator,
                bst: *BinarySearchTree(T, lessThanFn),
                order: Order,
            ) !@This() {
                var iter: @This() = .{
                    .allocator = allocator,
                    .stack = try .initCapacity(allocator, 0),
                    .bst = bst,
                    .order = order,
                };
                try iter.pushAll(bst.root);
                return iter;
            }

            pub fn deinit(self: *@This()) void {
                self.stack.deinit(self.allocator);
            }

            pub fn next(self: *@This()) !?T {
                const top = self.stack.popBack();
                if (top) |t| {
                    if (self.order == .ASC) try self.pushAll(t.right) else try self.pushAll(t.left);
                    return t.data;
                }
                return null;
            }

            fn pushAll(
                self: *@This(),
                root: ?*NodeT,
            ) !void {
                var node: ?*NodeT = root;
                while (node) |n| {
                    try self.stack.pushBack(self.allocator, n);
                    if (self.order == .ASC) node = n.left else node = n.right;
                }
            }
        };

        root: ?*NodeT = null,
        allocator: Allocator,

        pub fn init(allocator: Allocator) Self {
            return .{
                .allocator = allocator,
                .root = null,
            };
        }

        pub fn initRoot(allocator: Allocator, root: *NodeT) Self {
            return .{
                .allocator = allocator,
                .root = root,
            };
        }

        pub fn deinit(self: *Self) void {
            if (self.root) |r| r.deinit(self.allocator);
        }

        pub fn insert(self: *Self, data: T) !void {
            if (self.root) |root| {
                var current: ?*NodeT = root;
                while (true) {
                    if (current) |curr| {
                        if (curr.ltd(data)) {
                            if (curr.right != null)
                                current = curr.right
                            else {
                                curr.right = try NodeT.init(self.allocator, data);
                                break;
                            }
                        } else if (curr.gtd(data)) {
                            if (curr.left != null)
                                current = curr.left
                            else {
                                curr.left = try NodeT.init(self.allocator, data);
                                break;
                            }
                        } else break; // data already exists, do nothing
                    }
                }
            } else {
                self.root = try NodeT.init(self.allocator, data);
            }
        }

        pub fn contains(self: *Self, data: T) bool {
            if (self.root == null) return false;
            if (self.find(data)) |_| return true;
            return false;
        }

        /// Given a Binary Search Tree and a key value return the node in the BST
        /// having data equal to ‘key’ otherwise return nullptr.
        pub fn search(self: *Self, data: T) ?*NodeT {
            return find(self.root, data);
        }
        fn find(root: ?*NodeT, data: T) ?*NodeT {
            if (root) |rt| {
                var current: ?*NodeT = rt;
                while (current) |curr| {
                    if (curr.eqtd(data))
                        return curr
                    else if (curr.ltd(data))
                        current = curr.right
                    else
                        current = curr.left;
                }
                return null;
            } else return null;
        }

        /// maximum item in the binary search tree
        pub fn max(self: *Self) ?T {
            if (self.root == null) return null;
            if (rightmost(self.root.?)) |n| return n.data;
            return null;
        }
        fn rightmost(root: *NodeT) *NodeT {
            var current: ?*NodeT = root;
            while (current) |curr| {
                if (curr.right == null) break;
                current = curr.right;
            }
            return current.?;
        }

        /// minimum item in binary search tree
        pub fn min(self: *Self) ?T {
            if (self.root == null) return;
            if (leftmost(self.root.?)) |r| return r.data;
            return null;
        }
        fn leftmost(root: *NodeT) *NodeT {
            var current: ?*NodeT = root;
            while (current) |curr| {
                if (curr.left == null) break;
                current = curr.left;
            }
            return current.?;
        }

        /// Given a Binary Search Tree and a key, return the ceiling of the given key in the Binary Search Tree.
        /// Ceiling of a value refers to the value of the smallest node in the Binary Search Tree
        /// that is greater than or equal to the given key. If the ceiling node does not exist, return nullptr.
        pub fn ceil(self: *Self, data: T) ?T {
            if (self.root) |root| {
                var ceil_t: ?T = null;
                var current: ?*NodeT = root;
                while (current) |curr| {
                    if (curr.eqtd(data)) {
                        ceil_t = curr.data;
                        return ceil_t;
                    } else if (curr.ltd(data))
                        current = curr.right
                    else {
                        ceil_t = curr.data;
                        current = curr.left;
                    }
                }
                return ceil_t;
            } else return null;
        }

        /// Given a Binary Search Tree and a key, return the floor of the given key in the Binary Search Tree.
        /// Floor of a value refers to the value of the largest node in the Binary Search Tree
        /// that is smaller than or equal to the given key. If the floor node does not exist, return nullptr.
        pub fn floor(self: *Self, data: T) ?T {
            if (self.root) |root| {
                var floor_t: ?T = null;
                var current: ?*NodeT = root;
                while (current) |curr| {
                    if (curr.eqtd(data)) {
                        floor_t = curr.data;
                        return floor_t;
                    } else if (curr.ltd(data)) {
                        floor_t = curr.data;
                        current = curr.right;
                    } else current = curr.left;
                }
                return floor_t;
            } else return null;
        }

        pub fn delete(self: *Self, data: T) bool {
            if (self.root) |rt| {
                var current: ?*NodeT = rt;
                var dummy: ?*NodeT = null;
                while (current) |curr| {
                    if (curr.ltd(data)) {
                        if (curr.right != null and curr.right.?.data == data) {
                            dummy = curr.right;
                            curr.right = deletenext(curr.right.?);
                            break;
                        } else current = curr.right;
                    } else {
                        if (curr.left != null and curr.left.?.data == data) {
                            dummy = curr.left;
                            curr.left = deletenext(curr.left.?);
                            break;
                        } else current = curr.left;
                    }
                }
                if (dummy) |d| self.allocator.destroy(d);
                return true;
            }
            return false;
        }

        fn deletenext(root: *NodeT) ?*NodeT {
            if (root.left == null) return root.right;
            if (root.right == null) return root.left;
            const right_child = root.right;
            const right_most_of_left = rightmost(root.left.?);
            right_most_of_left.right = right_child;
            return root.left;
        }

        pub fn Inorder(
            self: *Self,
            ctx: anytype,
            visit: fn (ctx: @TypeOf(ctx), data: *const T) anyerror!void,
        ) !void {
            if (self.root == null) return;
            try inorderNode(self.root, ctx, visit);
        }
        fn inorderNode(
            node: ?*NodeT,
            ctx: anytype,
            visit: fn (ctx: @TypeOf(ctx), data: *const T) anyerror!void,
        ) !void {
            if (node) |n| {
                if (n.left) |l| try inorderNode(l, ctx, visit);
                try visit(ctx, &n.data);
                if (n.right) |r| try inorderNode(r, ctx, visit);
            }
        }

        // Given the root node of a binary search tree (BST) and an integer k.
        // Return the kth smallest and largest value (1-indexed) of all values of the nodes in the tree.
        pub fn KthSmallest(self: *Self, k: usize) ?T {
            if (self.root == null) return null;
            var count: usize = 0;
            const node = kthsmallestInorder(self.root, &count, k);
            if (node) |n| return n.data;
            return null;
        }
        pub fn KthLargest(self: *Self, k: usize) ?T {
            if (self.root == null) return null;
            var count: usize = 0;
            const node = kthlargestinorder(self.root, &count, k);
            if (node) |n| return n.data;
            return null;
        }

        fn kthsmallestInorder(node: ?*NodeT, count: *usize, k: usize) ?*NodeT {
            if (node) |n| {
                // Check left subtree first
                if (kthsmallestInorder(n.left, count, k)) |result|
                    return result;

                // Check current node
                count.* += 1;
                if (count.* == k)
                    return n;

                // Check right subtree
                if (kthsmallestInorder(n.right, count, k)) |result|
                    return result;
            }
            return null;
        }
        fn kthlargestinorder(node: ?*NodeT, count: *usize, k: usize) ?*NodeT {
            if (node) |n| {
                // Check left subtree first
                if (kthlargestinorder(n.right, count, k)) |result|
                    return result;

                // Check current node
                count.* += 1;
                if (count.* == k)
                    return n;

                // Check right subtree
                if (kthlargestinorder(n.left, count, k)) |result|
                    return result;
            }
            return null;
        }

        pub fn ValidBST(self: *Self, initailRange: ?Range) bool {
            if (self.root == null) return true;
            if (initailRange) |ir|
                return validbst(self.root, ir);
            return validbst(self.root, .{ .left = getMin(), .right = getMax() });
        }

        fn validbst(node: ?*NodeT, range: Range) bool {
            if (node) |n| {
                if (n.gtd(range.left) and n.ltd(range.right)) {
                    const left = validbst(n.left, .{ .left = range.left, .right = n.data });
                    const right = validbst(n.right, .{ .left = n.data, .right = range.right });
                    return left and right;
                } else return false;
            } else return true;
        }

        /// returns lowest common ancestor of a and b
        pub fn lowestCommonAncestor(self: *Self, a: T, b: T) ?T {
            if (self.root == null) return null;
            return lca(self.root, a, b);
        }
        fn lca(node: ?*NodeT, a: T, b: T) ?T {
            if (node) |n| {
                if (n.ltd(a) and n.ltd(b))
                    return lca(n.right, a, b);
                if (n.gtd(a) and n.gtd(b))
                    return lca(n.left, a, b);
                return n.data;
            } else return null;
        }

        /// construct the binary search tree from preorder
        pub fn ConstructBst(self: *Self, preorder: []const T, upperbound: ?T) !void {
            var i: usize = 0;
            const bound = if (upperbound) |ub| ub else getMax();
            self.root = try constructTree(preorder, &i, bound, self.allocator);
        }
        fn constructTree(preorder: []const T, i: *usize, bound: T, allocator: Allocator) !?*NodeT {
            if (i.* >= preorder.len or preorder[i.*] > bound) return null;
            const root = try NodeT.init(allocator, preorder[i.*]);
            i.* += 1;
            root.left = try constructTree(preorder, i, root.data, allocator);
            root.right = try constructTree(preorder, i, bound, allocator);
            return root;
        }

        /// Given a Binary Search Tree and a ‘key’ value which represents the data data of a node in this tree.
        /// Return the inorder predecessor and successor of the given node in the BST.
        pub fn Successor(self: *Self, k: T) ?T {
            var successor: ?*NodeT = null;
            var temp: ?*NodeT = self.root;

            while (temp) |n| {
                if (n.ltd(k) or n.eqtd(k))
                    temp = n.right
                else {
                    successor = n;
                    temp = n.left;
                }
            }
            return if (successor) |s| s.data else null;
        }
        pub fn Predecessor(self: *Self, k: T) ?T {
            var predecessor: ?*NodeT = null;
            var temp: ?*NodeT = self.root;

            while (temp) |n| {
                if (n.ltd(k)) {
                    predecessor = n;
                    temp = n.right;
                } else temp = n.left;
            }
            return if (predecessor) |s| s.data else null;
        }

        pub fn iterator(self: *Self, order: Iterator.Order) !Iterator {
            return try .init(self.allocator, self, order);
        }

        pub fn recoverBst(self: *Self) !void {
            const gen = struct {
                const context = struct {
                    first: ?*NodeT,
                    prev: ?*NodeT,
                    middle: ?*NodeT,
                    last: ?*NodeT,
                };

                fn Context(ctx: *context, data: *const T) !void {
                    const root_ptr: *NodeT = @alignCast(@fieldParentPtr("data", @constCast(data)));
                    if (ctx.prev != null and (root_ptr.data < ctx.prev.?.data)) {
                        if (ctx.first) |_| ctx.last = root_ptr else {
                            ctx.first = ctx.prev;
                            ctx.middle = root_ptr;
                        }
                    }
                    ctx.prev = root_ptr;
                }

                fn swap(a: *NodeT, b: *NodeT) void {
                    const temp = a.data;
                    a.data = b.data;
                    b.data = temp;
                }
            };

            var ctx = gen.context{
                .first = null,
                .last = null,
                .middle = null,
                .prev = null,
            };
            try self.Inorder(&ctx, gen.Context);
            if (ctx.first != null and ctx.last != null) {
                gen.swap(ctx.first.?, ctx.last.?);
            } else if (ctx.first != null and ctx.middle != null) {
                gen.swap(ctx.first.?, ctx.middle.?);
            }
        }

        fn getMin() T {
            const type_info = @typeInfo(T);
            return switch (type_info) {
                .int => std.math.minInt(T),
                .float => std.math.floatMin(T),
                else => @compileError("Invalid type\n"),
            };
        }
        fn getMax() T {
            const type_info = @typeInfo(T);
            return switch (type_info) {
                .int => std.math.maxInt(T),
                .float => std.math.floatMax(T),
                else => @compileError("Invalid type\n"),
            };
        }
    };
}
