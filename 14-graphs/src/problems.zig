const std = @import("std");
const Allocator = std.mem.Allocator;
const Deque = std.Deque;
const StringHashMap = std.StringHashMap;
const List = std.ArrayList;
const Graph = @import("graphs.zig");
const PriorityQueue = std.PriorityQueue;
const Order = std.math.Order;

pub const Point = struct {
    const Self = @This();
    row: i32,
    col: i32,
    pub fn Equal(self: Self, p: Self) bool {
        if (self.col == p.col and self.row == p.row) return true;
        return false;
    }
    pub fn Adjacent(self: Self) [4]Self {
        return [_]Self{
            Self{ .row = self.row - 1, .col = self.col },
            Self{ .row = self.row, .col = self.col + 1 },
            Self{ .row = self.row + 1, .col = self.col },
            Self{ .row = self.row, .col = self.col - 1 },
        };
    }

    pub fn ValidPoint(p: Self, n: usize, m: usize) bool {
        if (p.row >= 0 and p.row < n and p.col >= 0 and p.col < m) return true;
        return false;
    }
};
const drow = [_]i32{ -1, 0, 1, 0 };
const dcol = [_]i32{ 0, 1, 0, -1 };

/// Given an n x m grid, where each cell has the following values : 2 - represents a rotten orange , 1 - represents a Fresh orange , 0 - represents an Empty Cell .
/// Every minute, if a fresh orange is adjacent to a rotten orange in 4-direction ( upward, downwards, right, and left ) it becomes rotten.
/// Return the minimum number of minutes required such that none of the cells has a Fresh Orange. If it's not possible, return -1..
pub fn RottenOranges(
    allocator: Allocator,
    matrix: [][]u8,
) !?usize {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    var queue: Deque(struct { row: i32, cols: i32 }) = try .initCapacity(allocator, 0);
    defer queue.deinit(allocator);

    var visited: [][]bool = try allocator.alloc([]bool, matrix.len);
    defer allocator.free(visited);
    defer for (0..visited.len) |i| allocator.free(visited[i]);
    for (visited, 0..) |*row, i| {
        row.* = try allocator.alloc(bool, matrix[i].len);
        @memset(row.*, false);
    }

    // push initial rotten oranges
    for (0..n) |i| {
        for (0..m) |j| {
            if (matrix[i][j] == 2) {
                try queue.pushBack(allocator, .{ .row = @intCast(i), .cols = @intCast(j) });
                visited[i][j] = true;
            }
        }
    }

    var days: usize = 0;

    while (queue.len > 0) : (days += 1) {
        const count = queue.len;
        for (0..count) |_| {
            const orange = queue.popFront();
            if (orange) |index| {
                for (0..4) |i| {
                    const nrow: i32 = @intCast(index.row + drow[i]);
                    const ncol: i32 = @intCast(index.cols + dcol[i]);
                    if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and
                        !visited[@intCast(nrow)][@intCast(ncol)] and
                        matrix[@intCast(nrow)][@intCast(ncol)] == 1)
                    {
                        try queue.pushBack(allocator, .{ .row = @intCast(nrow), .cols = @intCast(ncol) });
                        visited[@intCast(nrow)][@intCast(ncol)] = true;
                    }
                }
            }
        }
    }

    for (0..n) |i|
        for (0..m) |j|
            if (visited[i][j] == false and matrix[i][j] == 1)
                return null;

    return days - 1;
}

/// An image is represented by a 2-D array of integers, each integer representing the pixel value of the image.
/// Given a coordinate (sr, sc) representing the starting pixel (row and column) of the flood fill, and a pixel value newColor, "flood fill" the image.
pub fn FloodFill(
    alloc: Allocator,
    matrix: [][]u8,
    fillColor: u8,
    initialPoint: Point,
) !void {
    const visited: [][]bool = try alloc.alloc([]bool, matrix.len);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);
    for (visited, 0..) |*row, i| {
        row.* = try alloc.alloc(bool, matrix[i].len);
        @memset(row.*, false);
    }
    floodfillDfs(
        initialPoint,
        matrix,
        visited,
        fillColor,
        matrix[@intCast(initialPoint.row)][@intCast(initialPoint.col)],
    );
}

fn floodfillDfs(
    pt: Point,
    matrix: [][]u8,
    visited: [][]bool,
    fillColor: u8,
    iniColor: u8,
) void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    // fill the color
    matrix[@intCast(pt.row)][@intCast(pt.col)] = fillColor;
    for (0..4) |i| {
        const nrow: i32 = @intCast(pt.row + drow[i]);
        const ncol: i32 = @intCast(pt.col + dcol[i]);
        if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and
            !visited[@intCast(nrow)][@intCast(ncol)] and // if not visited
            matrix[@intCast(nrow)][@intCast(ncol)] == iniColor // if it is same as initial color
        ) {
            visited[@intCast(nrow)][@intCast(ncol)] = true;
            floodfillDfs(.{ .row = nrow, .col = ncol }, matrix, visited, fillColor, iniColor);
        }
    }
}

/// Given a binary grid of N*M. Find the distance of the nearest 1 in the grid for each cell.
pub fn OneDistance(
    alloc: Allocator,
    matrix: [][]u8,
    result: [][]usize,
) !void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    const DistPoint = struct {
        pt: Point,
        dist: usize,
    };

    // visited
    var visited: [][]bool = try alloc.alloc([]bool, n);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);

    // queue
    var queue = try Deque(DistPoint).initCapacity(alloc, 0);
    defer queue.deinit(alloc);

    for (0..n) |i| {
        // set visited[i]
        visited[i] = try alloc.alloc(bool, matrix[i].len);
        @memset(visited[i], false);

        // set initial visited, queue and result
        for (0..matrix[i].len) |j| {
            result[i][j] = 0;
            if (matrix[i][j] == 1) {
                try queue.pushBack(
                    alloc,
                    .{ .pt = .{ .row = @intCast(i), .col = @intCast(j) }, .dist = 0 },
                );
                visited[i][j] = true;
            } else visited[i][j] = false;
        }
    }

    while (queue.len > 0) {
        const front = queue.popFront();
        if (front) |pt| {
            result[@intCast(pt.pt.row)][@intCast(pt.pt.col)] = pt.dist;
            for (0..4) |i| {
                const nrow = pt.pt.row + drow[i];
                const ncol = pt.pt.col + dcol[i];
                if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and !visited[@intCast(nrow)][@intCast(ncol)]) {
                    visited[@intCast(nrow)][@intCast(ncol)] = true;
                    try queue.pushBack(
                        alloc,
                        .{ .pt = .{ .row = nrow, .col = ncol }, .dist = pt.dist + 1 },
                    );
                }
            }
        }
    }
}

/// Given a matrix mat of size N x M where every element is either ‘O’ or ‘X’.
/// Replace all ‘O’ with ‘X’ that is surrounded by ‘X’.
/// An ‘O’ (or a set of ‘O’) is considered to be surrounded by ‘X’ if there are ‘X’ at locations just below,
/// just above just left, and just right of it.
pub fn SurroundedRegions(
    alloc: Allocator,
    matrix: [][]u8,
    result: [][]u8,
) !void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    var visited: [][]bool = try alloc.alloc([]bool, n);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);
    for (0..n) |i| {
        // set visited[i]
        visited[i] = try alloc.alloc(bool, matrix[i].len);
        @memset(visited[i], false);
        for (0..matrix[i].len) |j|
            result[i][j] = matrix[i][j];
    }

    // from matrix[0][0]... matrix[0][n-1]
    for (0..m - 1) |i| {
        if (matrix[0][i] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(0), .col = @intCast(i) }, matrix, visited);
    }

    // from (matrix[1][m-1]...matrix[n-1][m-1])
    for (1..n - 1) |i| {
        if (matrix[i][m - 1] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(i), .col = @intCast(n - 1) }, matrix, visited);
    }

    // from (matrix[n-1][m-2]...matrix[n-1][0])
    for (0..m - 2) |i| {
        if (matrix[n - 1][m - 2 - i] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(n - 1), .col = @intCast(n - 2 - i) }, matrix, visited);
    }
    // from (matrix[n-2][0]..matrix[1][0])
    for (1..n - 2) |i| {
        if (matrix[n - 2 - i][0] == 'O')
            surroundedRegionDfs(.{ .row = @intCast(n - 2 - i), .col = @intCast(0) }, matrix, visited);
    }

    for (0..n) |i| {
        for (0..matrix[i].len) |j| {
            if (!visited[i][j] and matrix[i][j] == 'O')
                result[i][j] = 'X';
        }
    }
}

fn surroundedRegionDfs(
    pt: Point,
    matrix: [][]u8,
    visited: [][]bool,
) void {
    // no of rows
    const n = matrix.len;
    // no of columns
    const m = matrix[0].len;

    for (0..4) |i| {
        const nrow: i32 = @intCast(pt.row + drow[i]);
        const ncol: i32 = @intCast(pt.col + dcol[i]);
        if (nrow >= 0 and nrow < n and ncol >= 0 and ncol < m and
            matrix[@intCast(nrow)][@intCast(ncol)] == 'O' and
            !visited[@intCast(nrow)][@intCast(ncol)] // if not visited
        ) {
            visited[@intCast(nrow)][@intCast(ncol)] = true;
            surroundedRegionDfs(.{ .row = nrow, .col = ncol }, matrix, visited);
        }
    }
}

/// You are given an N x M binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
/// A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
/// Find the number of land cells in the grid for which we cannot walk off the boundary of the grid in any number of moves..
pub fn NumberOfEnclaves() !void {
    // TODO
}

/// Given are the two distinct words startWord and targetWord, and a list denoting wordList of unique words of equal lengths.
/// Find the length of the shortest transformation sequence from startWord to targetWord..
/// In this problem statement, we need to keep the following conditions in mind:
///    - A word can only consist of lowercase characters.
///    - Only one letter can be changed in each transformation.
///    - Each transformed word must exist in the wordList including the targetWord.
///    - startWord may or may not be part of the wordList
pub fn WordLadder(
    alloc: Allocator,
    words: [][]const u8,
    source: []const u8,
    dist: []const u8,
) !usize {
    var wordmap = StringHashMap(void).init(alloc);
    defer wordmap.deinit();
    for (words) |word| try wordmap.put(word, {});

    var queue = try Deque(struct { word: []const u8, dist: usize }).initCapacity(alloc, 0);
    defer queue.deinit(alloc);
    try queue.pushBack(alloc, .{ .word = try alloc.dupe(u8, source), .dist = 1 });

    while (queue.len > 0) {
        const front = queue.popFront();
        if (front) |queue_data| {
            defer alloc.free(queue_data.word);
            if (std.mem.eql(u8, queue_data.word, dist)) {
                const distance = queue_data.dist;
                while (queue.popBack()) |f| alloc.free(f.word);
                return distance;
            }
            for (0..queue_data.word.len) |i| {
                var word = try alloc.dupe(u8, queue_data.word);
                defer alloc.free(word);

                for (0..26) |j| {
                    word[i] = 'a' + @as(u8, @intCast(j));
                    if (wordmap.contains(word)) {
                        _ = wordmap.remove(word);
                        try queue.pushBack(alloc, .{
                            .word = try alloc.dupe(u8, word),
                            .dist = queue_data.dist + 1,
                        });
                    }
                }
            }
        }
    }
    return 0;
}

/// Given a boolean 2D matrix grid of size N x M. You have to find the number of distinct islands where
/// a group of connected 1s (horizontally or vertically) forms an island. Two islands are considered
/// to be distinct if and only if one island
/// is equal to another (not rotated or reflected).
pub fn NumberOfIsland(
    alloc: Allocator,
    islands: [][]u8,
) !usize {
    var number_of_island: usize = 0;
    // no of rows
    const n = islands.len;
    // no of columns
    const m = islands[0].len;

    var visited: [][]bool = try alloc.alloc([]bool, n);
    defer alloc.free(visited);
    defer for (0..visited.len) |i| alloc.free(visited[i]);
    for (0..n) |i| {
        visited[i] = try alloc.alloc(bool, islands[i].len);
        @memset(visited[i], false);
    }

    for (0..n) |row| {
        for (0..m) |col| {
            if (islands[row][col] == 1 and !visited[row][col]) {
                number_of_island += 1;
                var queue = try Deque(Point).initCapacity(alloc, 0);
                defer queue.deinit(alloc);
                try queue.pushBack(alloc, .{ .row = @intCast(row), .col = @intCast(col) });
                visited[row][col] = true;
                while (queue.len > 0) {
                    const front = queue.popBack();
                    if (front) |curr| {
                        for (0..4) |i| {
                            const nrow = curr.row + drow[i];
                            const ncol = curr.col + dcol[i];
                            if (nrow >= 0 and
                                nrow < n and
                                ncol >= 0 and
                                ncol < m and
                                !visited[@intCast(nrow)][@intCast(ncol)] and
                                islands[@intCast(nrow)][@intCast(ncol)] == 1)
                            {
                                visited[@intCast(nrow)][@intCast(ncol)] = true;
                                try queue.pushBack(alloc, .{ .row = @intCast(nrow), .col = @intCast(ncol) });
                            }
                        }
                    }
                }
            }
        }
    }
    return number_of_island;
}

pub fn AlienDictionary(
    alloc: Allocator,
    dict: *(List([]const u8)),
    ctx: anytype,
    visit: fn (@TypeOf(ctx), ch: u8) anyerror!void,
) !void {
    const GraphType = Graph.Graph(u8, true);
    const Node = struct {
        data: u8,
        node: GraphType.Node,
    };
    const AlphabetHashMap = std.AutoHashMap(u8, Node);

    var alphabet: AlphabetHashMap = .init(alloc);
    defer alphabet.deinit();

    var graph = try GraphType.init(alloc);
    defer graph.deinit();

    for (0..dict.items.len - 1) |i| {
        for (0..dict.items[i].len) |j| {
            if (alphabet.get(dict.items[i][j])) |_| continue;
            try alphabet.put(dict.items[i][j], .{ .data = @intCast(dict.items[i][j]), .node = .{ .index = null } });
        }
    }

    var iter = alphabet.iterator();
    while (iter.next()) |entry| {
        try graph.insert(&(entry.value_ptr.node));
    }

    for (0..dict.items.len - 1) |i| {
        const str1 = dict.items[i];
        const str2 = dict.items[i + 1];
        const len: usize = @min(str1.len, str2.len);
        for (0..len) |j| {
            if (str1[j] != str2[j]) {
                try graph.addEdge(&(alphabet.getPtr(str1[j]).?.node), &(alphabet.getPtr(str2[j]).?.node), 0);
                break;
            }
        }
    }

    var result: List(u8) = try .initCapacity(alloc, 0);
    defer result.deinit(alloc);

    const gen = struct {
        fn visit_Z(_: void, node: *GraphType.Node) !void {
            const data: *Node = @fieldParentPtr("node", @constCast(node));
            try visit(ctx, data.data);
        }
    };
    try graph.TopologicalSortBfs({}, gen.visit_Z);
}

/// Problem Statement: Given an n * m matrix grid where each element can either be 0 or 1.
/// You need to find the shortest distance between a given source cell to a destination cell.
/// The path can only be created out of a cell if its value is 1.
/// If the path is not possible between the source cell and the destination cell, then return -1.
/// Note: You can move into an adjacent cell if that adjacent cell is filled with element 1.
/// Two cells are adjacent if they share a side.
/// In other words, you can move in one of four directions, Up, Down, Left, and Right.
pub fn ShortestSourceDestination(
    alloc: Allocator,
    grid: [][]u8,
    source: Point,
    dest: Point,
) !?usize {
    const DistPoint = struct {
        dist: usize,
        point: Point,
    };
    // no of rows
    const n = grid.len;
    // no of columns
    const m = grid[0].len;

    var distance: [][]usize = try alloc.alloc([]usize, n);
    defer alloc.free(distance);
    defer for (0..distance.len) |i| alloc.free(distance[i]);
    for (0..n) |i| {
        distance[i] = try alloc.alloc(usize, grid[i].len);
        @memset(distance[i], std.math.maxInt(usize));
    }
    distance[@intCast(source.row)][@intCast(source.col)] = 0;

    var queue = try Deque(DistPoint).initCapacity(alloc, 0);
    defer queue.deinit(alloc);
    try queue.pushBack(
        alloc,
        .{ .dist = 0, .point = source },
    );

    while (queue.len > 0) {
        const top = queue.popFront();
        if (top) |dist_point| {
            const dist = dist_point.dist;
            for (dist_point.point.Adjacent()) |p| {
                if (!p.ValidPoint(n, m)) continue;
                const r: usize = @intCast(p.row);
                const c: usize = @intCast(p.col);
                if (grid[r][c] == 1 and dist + 1 < distance[r][c]) {
                    distance[r][c] = dist + 1;
                    if (r == dest.row and c == dest.col) return 1 + dist;
                    try queue.pushBack(alloc, .{ .dist = dist + 1, .point = p });
                }
            }
        }
    }
    return null;
}

/// Problem Statement: You are a hiker preparing for an upcoming hike.
/// You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of the cell (row, col).
/// You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e.,0-indexed).
/// You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
///
/// A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
pub fn MinimunEffort(
    alloc: Allocator,
    grid: [][]i32,
    source: Point,
    dest: Point,
) !?usize {
    const DiffPoint = struct {
        diff: usize,
        point: Point,
    };
    // no of rows
    const n = grid.len;
    // no of columns
    const m = grid[0].len;

    var effort: [][]usize = try alloc.alloc([]usize, n);
    defer alloc.free(effort);
    defer for (0..effort.len) |i| alloc.free(effort[i]);
    for (0..n) |i| {
        effort[i] = try alloc.alloc(usize, grid[i].len);
        @memset(effort[i], std.math.maxInt(usize));
    }
    effort[@intCast(source.row)][@intCast(source.col)] = 0;

    const Gen = struct {
        fn lessThan(context: void, a: DiffPoint, b: DiffPoint) Order {
            _ = context;
            return std.math.order(a.diff, b.diff);
        }
    };
    const MinHeap = PriorityQueue(DiffPoint, void, Gen.lessThan);
    var pq: MinHeap = .empty;
    defer pq.deinit(alloc);
    try pq.push(
        alloc,
        .{ .diff = 0, .point = source },
    );

    while (pq.items.len > 0) {
        const top = pq.pop();
        if (top) |diff_point| {
            const diff = diff_point.diff;
            const curr_r: usize = @intCast(diff_point.point.row);
            const curr_c: usize = @intCast(diff_point.point.col);
            if (curr_r == dest.row and curr_c == dest.col) return diff;
            for (diff_point.point.Adjacent()) |p| {
                if (!p.ValidPoint(n, m)) continue;
                const r: usize = @intCast(p.row);
                const c: usize = @intCast(p.col);
                const effort_needed = @max(diff, @abs(grid[curr_r][curr_c] - grid[r][c]));
                if (effort_needed < effort[r][c]) {
                    effort[r][c] = effort_needed;
                    try pq.push(
                        alloc,
                        .{ .diff = effort_needed, .point = p },
                    );
                }
            }
        }
    }
    return null;
}

/// Problem Statement: There are n cities and m edges connected by some number of flights.
/// You are given an array of flights where flights[i] = [ fromi, toi, pricei] indicates
/// that there is a flight from city fromi to city toi with cost price.
/// You have also given three integers src, dst, and k, and return the cheapest price from src to dst with at most k stops.
/// If there is no such route, return -1.
pub fn CheapestFlight(
    alloc: Allocator,
    graph: *const Graph.Graphusize,
    K: usize, // stops
    src: *const Graph.Graphusize.Node,
    dest: *const Graph.Graphusize.Node,
) !?usize {
    const StopNodeDist = struct {
        stops: usize,
        node: *const Graph.Graphusize.Node,
        dist: usize,
    };

    const n = graph.vertices.items.len;

    var distance: []usize = try alloc.alloc(usize, n);
    defer alloc.free(distance);
    distance[src.index.?] = 0;

    var queue: Deque(StopNodeDist) = try .initCapacity(alloc, 0);
    defer queue.deinit(alloc);
    try queue.pushBack(alloc, .{ .stops = 0, .node = src, .dist = 0 });

    while (queue.len > 0) {
        const front = queue.popFront();
        if (front) |stopnodedist| {
            const stops = stopnodedist.stops;
            const node = stopnodedist.node;
            const dist = stopnodedist.dist;
            const node_index = node.index.?;

            if (stops > K) continue;
            for (graph.adj.items[node_index].items) |edge| {
                const dest_index = edge.destination.index.?;
                if (dist + edge.weight < distance[dest_index] and stops <= K) {
                    distance[dest_index] = dist + edge.weight;
                    try queue.pushBack(alloc, .{
                        .stops = stops + 1,
                        .node = edge.destination,
                        .dist = dist + edge.weight,
                    });
                }
            }
        }
    }
    if (distance[dest.index.?] == std.math.maxInt(usize)) return null;
    return distance[dest.index.?];
}
