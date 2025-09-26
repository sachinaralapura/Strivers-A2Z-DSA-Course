const std = @import("std");
const stdout = std.io.getStdOut().writer();

const Allocator = std.mem.Allocator;
var gpa = std.heap.GeneralPurposeAllocator(.{}).init;

fn CreateMatrix(comptime T: type) type {
    return struct {
        data: []T,
        rows: usize,
        cols: usize,
        allocator: Allocator,

        pub fn init(allocator: Allocator, rows: usize, cols: usize) !@This() {
            if (rows == 0 or cols == 0) {
                return error.InvalidDimensions;
            }
            const data = try allocator.alloc(T, rows * cols);
            @memset(data, 0);
            return @This(){ .data = data, .rows = rows, .cols = cols, .allocator = allocator };
        }

        pub fn deinit(self: *@This()) void {
            self.allocator.free(self.data);
            self.data = undefined;
            self.rows = 0;
            self.cols = 0;
        }

        fn checkBoundry(self: *const @This(), row: usize, col: usize) bool {
            return row >= self.rows or col >= self.cols;
        }

        pub fn get(self: *const @This(), row: usize, col: usize) !T {
            if (self.checkBoundry(row, col)) {
                return error.IndexOutOfBound;
            }
            return self.data[row * self.cols + col];
        }

        pub fn set(self: *@This(), row: usize, col: usize, value: T) !void {
            if (self.checkBoundry(row, col)) {
                return error.IndexOutOfBound;
            }
            self.data[row * self.cols + col] = value;
        }

        pub fn String(self: *const @This()) ![]u8 {
            var buffer = std.ArrayList(u8).init(self.allocator);
            // in case of error deinit buffer
            errdefer buffer.deinit();

            // Add matrix dimensions header
            try std.fmt.format(buffer.writer(), "Matrix ({d}x{d}) of type {s}:\n", .{ self.rows, self.cols, @typeName(T) });
            for (0..self.rows) |r| {
                for (0..self.cols) |c| {
                    const value = try self.get(r, c);
                    try std.fmt.format(buffer.writer(), "{} ", .{value});
                }
                // Add a newline after each row
                try buffer.append('\n');
            }
            return try buffer.toOwnedSlice();
        }

        pub fn print(self: *const @This()) !void {
            const str = try self.String();
            defer self.allocator.free(str);
            try stdout.print("{s}\n", .{str});
        }
    };
}

const BMatrix = CreateMatrix(u8);
const DpMatrix = CreateMatrix(usize);

fn largest_sqare(allocator: Allocator, mat: *const BMatrix) !usize {
    const n: usize = mat.rows;
    const m: usize = mat.cols;
    var dp: DpMatrix = try DpMatrix.init(allocator, n, m);
    defer dp.deinit();

    var max: usize = 0;
    for (0..n) |i| {
        for (0..m) |j| {
            const val = try mat.get(i, j);
            if (val == 0) continue;

            var left: usize, var top: usize, var diag: usize = .{ 0, 0, 0 };

            if (i > 0 and j > 0) {
                left = try dp.get(i, j - 1);
                top = try dp.get(i - 1, j);
                diag = try dp.get(i - 1, j - 1);
            }
            const dpValue = @min(left, top, diag) + 1;
            if (dpValue > max) {
                max = dpValue;
            }
            try dp.set(i, j, dpValue);
        }
    }
    try dp.print();
    return max;
}

pub fn main() !void {
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    var prng = std.Random.DefaultPrng.init(@intCast(std.time.nanoTimestamp()));
    var rng = prng.random();

    const rows: usize = 10000;
    const cols: usize = 10000;

    var matrix: BMatrix = try BMatrix.init(allocator, rows, cols);
    defer matrix.deinit();

    for (0..rows) |i| {
        for (0..cols) |j| {
            try matrix.set(i, j, @intFromBool(rng.boolean()));
            try matrix.set(i, j, 1);
        }
    }
    try matrix.print();

    const largest: usize = try largest_sqare(allocator, &matrix);
    try stdout.print("{d}\n", .{largest});
}
