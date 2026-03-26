const std = @import("std");
const problems = @import("problems.zig");
const List = std.ArrayList;
const expect = std.testing.expect;

test "Rotten Oranges" {
    const allocator = std.testing.allocator;
    // var rows = [_][3]u8{
    //     .{ 0, 1, 2 },
    //     .{ 0, 1, 1 },
    //     .{ 2, 1, 1 },
    // };
    var rows = [_][3]u8{
        .{ 2, 1, 1 },
        .{ 1, 2, 1 },
        .{ 0, 0, 0 },
    };
    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
    };
    const expected: usize = 2;
    const actual = try problems.RottenOranges(allocator, matrix[0..]);
    try expect(expected == actual);
}

test "FloodFill" {
    const allocator = std.testing.allocator;
    var rows = [_][3]u8{ .{ 1, 2, 2 }, .{ 2, 2, 1 }, .{ 2, 1, 2 } };
    var matrix = [_][]u8{ rows[0][0..], rows[1][0..], rows[2][0..] };

    var expected = [_][3]u8{ .{ 1, 3, 3 }, .{ 3, 3, 1 }, .{ 3, 1, 2 } };

    try problems.FloodFill(
        allocator,
        matrix[0..],
        3,
        .{ .row = 2, .col = 0 },
    );

    for (0..matrix.len) |i|
        for (0..matrix.len) |j|
            try expect(matrix[i][j] == expected[i][j]);
}

test "OneDistance" {
    const allocator = std.testing.allocator;

    var rows = [_][3]u8{
        .{ 0, 0, 0 },
        .{ 0, 1, 0 },
        .{ 1, 0, 1 },
    };
    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
    };

    // result
    var result: [][]usize = try allocator.alloc([]usize, matrix.len);
    for (result, 0..) |*row, i| {
        row.* = try allocator.alloc(usize, matrix[i].len);
        @memset(row.*, 0);
    }
    defer allocator.free(result);
    defer for (0..result.len) |i| allocator.free(result[i]);

    var expected = [_][3]u8{
        .{ 2, 1, 2 },
        .{ 1, 0, 1 },
        .{ 0, 1, 0 },
    };
    try problems.OneDistance(allocator, matrix[0..], result);

    for (0..result.len) |i|
        for (0..result.len) |j|
            try expect(result[i][j] == expected[i][j]);
}

test "SurroundRegions" {
    const allocator = std.testing.allocator;

    const X: u8 = 'X';
    const O: u8 = 'O';
    var rows = [_][4]u8{
        .{ X, X, X, X },
        .{ X, O, O, X },
        .{ X, O, X, X },
        .{ X, O, X, X },
        .{ X, X, O, O },
    };

    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
        rows[3][0..],
        rows[4][0..],
    };

    var result: [][]u8 = try allocator.alloc([]u8, matrix.len);
    for (result, 0..) |*row, i| {
        row.* = try allocator.alloc(u8, matrix[i].len);
        @memset(row.*, 0);
    }
    defer allocator.free(result);
    defer for (0..result.len) |i| allocator.free(result[i]);

    try problems.SurroundedRegions(allocator, matrix[0..], result);

    var expected = [_][4]u8{
        .{ X, X, X, X },
        .{ X, X, X, X },
        .{ X, X, X, X },
        .{ X, X, X, X },
        .{ X, X, O, O },
    };

    for (0..result.len) |i|
        for (0..result[i].len) |j|
            try expect(result[i][j] == expected[i][j]);
}

test "WordLadder" {
    const allocator = std.testing.allocator;
    var words = [_][]const u8{ "des", "der", "dfr", "dgt", "dfs" };
    const source = "der";
    const dist = "dfs";
    const res = try problems.WordLadder(allocator, &words, source, dist);
    try expect(3 == res);
}

test "NumberOfIsland" {
    const allocator = std.testing.allocator;

    var rows = [_][5]u8{
        .{ 1, 1, 0, 1, 1 },
        .{ 1, 0, 0, 0, 0 },
        .{ 0, 0, 0, 0, 1 },
        .{ 1, 1, 0, 1, 1 },
    };

    var matrix = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
        rows[3][0..],
    };

    const expected = try problems.NumberOfIsland(allocator, matrix[0..]);
    try expect(4 == expected);
}

test "Alien Dictionary" {
    const allocator = std.testing.allocator;
    var dict: List([]const u8) = try .initCapacity(allocator, 0);
    defer dict.deinit(allocator);

    const gen = struct {
        fn visit(_: void, ch: u8) !void {
            std.debug.print("{c}\n", .{ch});
        }
    };

    // const wordszero = [5][]const u8{ "kaa", "akcd", "akca", "cak", "cad" };
    // const wordsOne = [5][]const u8{ "baa", "abcd", "abca", "cab", "cad" };
    // const wordsTwo = [5][]const u8{ "wrt", "wrf", "er", "ett", "rftt" };
    const wordsThree = [3][]const u8{ "z", "x", "z" };

    for (wordsThree) |word| try dict.append(allocator, word);
    try problems.AlienDictionary(allocator, &dict, {}, gen.visit);
}

test "Shortest Distance from source to destination" {
    const allocator = std.testing.allocator;
    var rows = [_][4]u8{
        .{ 1, 1, 1, 1 },
        .{ 1, 1, 0, 1 },
        .{ 1, 1, 1, 1 },
        .{ 1, 1, 0, 0 },
        .{ 1, 0, 0, 1 },
    };
    var grid = [_][]u8{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
        rows[3][0..],
        rows[4][0..],
    };
    var res = try problems.ShortestSourceDestination(
        allocator,
        grid[0..],
        .{ .row = 0, .col = 1 },
        .{ .row = 4, .col = 3 },
    );
    try expect(null == res);

    res = try problems.ShortestSourceDestination(
        allocator,
        grid[0..],
        .{ .row = 0, .col = 1 },
        .{ .row = 4, .col = 0 },
    );
    try expect(5 == res);

    res = try problems.ShortestSourceDestination(
        allocator,
        grid[0..],
        .{ .row = 0, .col = 1 },
        .{ .row = 2, .col = 2 },
    );
    try expect(3 == res);

    res = try problems.ShortestSourceDestination(
        allocator,
        grid[0..],
        .{ .row = 0, .col = 1 },
        .{ .row = 2, .col = 3 },
    );
    try expect(4 == res);
}

test "Minimum Effort" {
    const allocator = std.testing.allocator;
    var rows = [_][5]i32{
        .{ 1, 2, 1, 1, 1 },
        .{ 1, 2, 1, 2, 1 },
        .{ 1, 2, 1, 2, 1 },
        .{ 1, 1, 1, 2, 1 },
    };
    var grid = [_][]i32{
        rows[0][0..],
        rows[1][0..],
        rows[2][0..],
        rows[3][0..],
    };

    var res = try problems.MinimunEffort(
        allocator,
        grid[0..],
        .{ .row = 0, .col = 0 },
        .{ .row = 3, .col = 4 },
    );
    if (res) |r| try expect(0 == r);

    var rows1 = [_][3]i32{
        .{ 1, 2, 2 },
        .{ 3, 8, 2 },
        .{ 5, 3, 5 },
    };
    var grid1 = [_][]i32{
        rows1[0][0..],
        rows1[1][0..],
        rows1[2][0..],
    };

    res = try problems.MinimunEffort(
        allocator,
        grid1[0..],
        .{ .row = 0, .col = 0 },
        .{ .row = 2, .col = 2 },
    );
    if (res) |r| try expect(2 == r);
}
