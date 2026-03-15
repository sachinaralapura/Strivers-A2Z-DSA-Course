const std = @import("std");
const Allocator = std.mem.Allocator;
const Deque = std.Deque;
const StringHashMap = std.StringHashMap;
const List = std.ArrayList;
const Grpah = @import("graphs.zig").Graph;

pub const Point = struct {
    row: i32,
    col: i32,
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
    var visited: [][]bool = try alloc.alloc([]bool, matrix.len);
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
    const GraphType = Grpah(u8, true);
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
