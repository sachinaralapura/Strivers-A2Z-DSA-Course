// Problem Statement: Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

// Implement the LRUCache class:

// LRUCache(int capacity): Initialize the LRU cache with positive size capacity.
// int get(int key): Return the value of the key if the key exists, otherwise return -1.
// void put(int key, int value): Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.

// The functions get and put must each run in O(1) average time complexity.

const std = @import("std");
const HashMap = std.AutoArrayHashMap;
const Allocator = std.mem.Allocator;
const common = @import("common.zig");
const Job = common.JobLru;
const Node = common.Node;
const hasId = common.hasId;

fn LruCache(comptime T: type, comptime K: type) type {
    hasId(T, K, "id");
    return struct {
        const Self = @This();
        const NodeType = Node(T);
        const NodeMap = HashMap(K, *NodeType);

        allocator: Allocator,
        capacity: usize,
        head: ?*NodeType,
        tail: ?*NodeType,
        map: NodeMap,

        fn init(allocator: Allocator, cap: usize) Self {
            return .{
                .allocator = allocator,
                .capacity = cap,
                .head = null,
                .tail = null,
                .map = NodeMap.init(allocator),
            };
        }

        fn deinit(self: *Self) void {
            while (self.head) |node| {
                self.head = node.next;
                self.allocator.destroy(node);
            }
            self.map.deinit();
        }

        fn unlinkNode(self: *Self, node: *NodeType) void {
            const prev = node.prev;
            const next = node.next;

            if (prev) |p| {
                p.next = next;
            } else self.head = next;

            if (next) |n| {
                n.prev = prev;
            } else self.tail = prev;

            node.prev = null;
            node.next = null;
        }

        fn freeNode(self: *Self, node: *NodeType) void {
            self.unlinkNode(node);
            self.allocator.destroy(node);
        }

        fn addNode(self: *Self, node: *NodeType) void {
            node.prev = null;
            node.next = self.head;
            if (self.head) |head| {
                head.prev = node;
            } else self.tail = node; // first node
            self.head = node;
        }

        pub fn get(self: *Self, id: K) !?T {
            if (self.map.get(id)) |node| {
                self.unlinkNode(node);
                self.addNode(node);
                return node.data;
            }
            return null;
        }

        pub fn put(self: *Self, entry: T) !void {
            if (self.map.get(entry.id)) |node| {
                node.data = entry;
                self.unlinkNode(node);
                self.addNode(node);
                return;
            }

            if (self.map.count() >= self.capacity) {
                const tail = self.tail.?;
                _ = self.map.swapRemove(tail.data.id);
                self.freeNode(tail);
            }

            const node = try NodeType.init(self.allocator, entry);
            self.addNode(node);
            try self.map.put(entry.id, node);
        }
    };
}

pub fn main() !void {
    const out = std.fs.File.stdout();
    var buffer: [4096]u8 = undefined;
    var std_writer = out.writer(&buffer);
    const stdout = &std_writer.interface;

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    const allocator: Allocator = gpa.allocator();
    defer _ = gpa.deinit();
    var lru = LruCache(Job, usize).init(allocator, 2);
    defer lru.deinit();

    try lru.put(Job.init(1, "one"));
    try lru.put(Job.init(2, "two"));

    if (try lru.get(1)) |job| {
        try stdout.print("{f}", .{job});
    } else try stdout.print("Job not found\n", .{});

    try lru.put(Job.init(3, "three"));

    if (try lru.get(2)) |job| {
        try stdout.print("{f}", .{job});
    } else try stdout.print("Job not found\n", .{});

    try lru.put(Job.init(4, "four"));

    if (try lru.get(1)) |job| {
        try stdout.print("{f}", .{job});
    } else try stdout.print("Job not found\n", .{});

    if (try lru.get(3)) |job| {
        try stdout.print("{f}", .{job});
    } else try stdout.print("Job not found\n", .{});

    if (try lru.get(4)) |job| {
        try stdout.print("{f}", .{job});
    } else try stdout.print("Job not found\n", .{});

    try stdout.flush();
}
