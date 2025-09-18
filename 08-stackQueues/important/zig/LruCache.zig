const std = @import("std");
const Allocator = std.mem.Allocator;
var gpa = std.heap.GeneralPurposeAllocator(.{}).init;

fn Node(comptime T: type) type {
    return struct {
        const Self = @This();
        key: usize,
        value: *T,
        next: ?*Self,
        prev: ?*Self,

        pub fn init(allocator: Allocator, key: usize, value: ?T) !*Self {
            var node = try allocator.create(Self);
            const new_value = try allocator.create(T);
            if (value != null) {
                new_value.* = value.?;
            }

            node.key = key;
            node.value = new_value;
            node.next = null;
            node.prev = null;
            return node;
        }

        pub fn deinit(node: *Self, allocator: Allocator) void {
            allocator.destroy(node.value);
            allocator.destroy(node);
        }
    };
}

fn LruCache(comptime T: type) type {
    const TNode = Node(T);
    const NodeMap = std.AutoHashMap(usize, *TNode);
    return struct {
        const Self = @This();
        capacity: usize,
        mpp: NodeMap,
        head: *TNode,
        tail: *TNode,
        allocator: Allocator,

        pub fn init(allocator: Allocator, _cap: usize) !*Self {
            const lrucache = try allocator.create(Self);
            lrucache.allocator = allocator;
            lrucache.capacity = _cap;
            lrucache.head = try TNode.init(allocator, 0, null);
            lrucache.tail = try TNode.init(allocator, 0, null);
            lrucache.mpp = NodeMap.init(allocator);
            lrucache.head.next = lrucache.tail;
            lrucache.tail.prev = lrucache.head;
            return lrucache;
        }

        pub fn deinit(self: *Self) void {
            var currentNode: *TNode = self.head;
            var nextNode: *TNode = undefined;
            while (currentNode.next != null) {
                nextNode = currentNode.next.?;
                currentNode.deinit(currentNode, self.allocator);
                currentNode = nextNode;
            }
            self.mpp.deinit();
            self.allocator.destroy(self);
        }

        pub fn addNode(self: *Self, node: *TNode) void {
            var temp: *TNode = self.head.next.?;
            node.next = temp;
            node.prev = self.head;
            self.head.next = node;
            temp.prev = node;
        }

        pub fn deleteNode(self: *Self, node: *TNode) void {
            var delprev = node.prev;
            var delnext = node.next;
            delprev.?.next = delnext;
            delnext.?.prev = delprev;
            node.deinit(self.allocator);
        }

        pub fn get(self: *Self, _key: usize) !?T {
            if (self.mpp.contains(_key)) {
                const temp = self.mpp.get(_key).?;
                const res: T = temp.value.*;
                _ = self.mpp.remove(_key);
                self.deleteNode(temp);
                self.addNode(temp);
                _ = try self.mpp.put(_key, self.head.next.?);
                return res;
            }
            return null;
        }

        pub fn put(self: *Self, _key: usize, value: T) !void {
            if (self.mpp.contains(_key)) {
                const existingNode = self.mpp.get(_key).?;
                _ = self.mpp.remove(_key);
                self.deleteNode(existingNode);
            }
            if (self.mpp.count() == self.capacity) {
                _ = self.mpp.remove(self.tail.prev.?.key);
                self.deleteNode(self.tail.prev.?);
            }
            self.addNode(try TNode.init(self.allocator, _key, value));
            try self.mpp.put(_key, self.head.next.?);
        }

        pub fn print(self: *Self) void {
            var temp: ?*TNode = self.head.next.?;
            while (temp.?.next != null) {
                std.debug.print("{d} : {s}\n", .{ temp.?.key, temp.?.value.* });
                temp = temp.?.next;
            }
        }
    };
}

pub fn main() !void {
    const lruCacheString = LruCache([]const u8);
    const allocator: Allocator = gpa.allocator();
    var lrucache = try lruCacheString.init(allocator, 2);
    try lrucache.put(1, "one");
    try lrucache.put(2, "two");
    try lrucache.put(3, "three");
    try lrucache.put(4, "four");
    try lrucache.put(5, "five");
    const temp = try lrucache.get(3);
    if (temp != null) {
        std.debug.print("{s}\n", .{temp.?});
    }
    lrucache.print();
}
