const std = @import("std");
const Allocator = std.mem.Allocator;

const Order = std.math.Order;
const List = std.ArrayList;
const Deque = std.Deque;
const StringHashMap = std.StringHashMap;
const PriorityQueue = std.PriorityQueue;
const Graph = @import("graphs.zig").Graph;

const assert = std.debug.assert;
pub fn Disjoint(comptime W: type, comptime isDirected: bool) type {
    return struct {
        const Self = @This();
        const GraphType = Graph(W, isDirected);
        const Node = GraphType.Node;

        allocator: Allocator,
        graph: GraphType,

        rank: List(usize),
        parent: List(*Node),
        extraEdgeCount: usize = 0,

        pub fn init(allocator: Allocator) !Self {
            return .{
                .allocator = allocator,
                .graph = try GraphType.init(allocator),
                .parent = try .initCapacity(allocator, 0),
                .rank = try .initCapacity(allocator, 0),
            };
        }
        pub fn initDirected(allocator: Allocator, is_directed: bool) !Self {
            return .{
                .allocator = allocator,
                .vertices = try .initCapacity(allocator, 0),
                .adj = try .initCapacity(allocator, 0),
                .is_directed = is_directed,
            };
        }

        pub fn deinit(self: *Self) void {
            self.graph.deinit();
            self.rank.deinit(self.allocator);
            self.parent.deinit(self.allocator);
        }
        pub fn insert(self: *Self, node: *Node) !void {
            try self.graph.insert(node);
            const index = node.index.?;
            try self.parent.ensureTotalCapacity(self.allocator, index + 1);
            try self.rank.ensureTotalCapacity(self.allocator, index + 1);
            self.parent.items.len = index + 1;
            self.rank.items.len = index + 1;
            self.parent.items[index] = node;
            self.rank.items[index] = 0;
        }

        pub fn Union(self: *Self, u: *Node, v: *Node, w: W) !void {
            try self.graph.addEdge(u, v, w);
            const ultimate_parent_u = self.findParent(u);
            const ultimate_parent_v = self.findParent(v);

            const up_rank_u = self.rankOf(ultimate_parent_u);
            const up_rank_v = self.rankOf(ultimate_parent_v);

            const up_index_u = ultimate_parent_u.index.?;
            const up_index_v = ultimate_parent_v.index.?;

            // if ultimate parent are same
            if (up_index_u == up_index_v) {
                self.extraEdgeCount += 1;
                return;
            }
            if (up_rank_u < up_rank_v) {
                self.parent.items[up_index_u] = ultimate_parent_v;
            } else if (up_rank_v < up_rank_u) {
                self.parent.items[up_index_v] = ultimate_parent_u;
            } else {
                self.parent.items[up_index_v] = ultimate_parent_u;
                self.rank.items[up_index_u] += 1;
            }
        }

        /// return the parent of the node
        fn parentOf(self: *Self, node: *Node) *Node {
            return self.parent.items[node.index.?];
        }

        /// return the rank of a node
        fn rankOf(self: *Self, node: *Node) usize {
            return self.rank.items[node.index.?];
        }

        /// path compression
        pub fn findParent(self: *Self, node: *Node) *Node {
            const index = node.index.?;
            const parent = self.parentOf(node);
            const parent_index = parent.index.?;

            if (index == parent_index)
                return node;
            if (self.parent.items.len > index)
                self.parent.items[index] = self.findParent(self.parentOf(node));
            return self.parent.items[index];
        }

        pub fn NoOperationToConnect(self: *Self) !?usize {
            var countConnectedComp: usize = 0;
            for (self.graph.vertices.items) |node| {
                const parent = self.findParent(node);
                if (parent.index.? == node.index.?)
                    countConnectedComp += 1;
            }
            if (self.extraEdgeCount >= (countConnectedComp - 1)) return countConnectedComp - 1;
            return null;
        }
    };
}
