// Problem Statement: Find the validity of an input string s that only contains the letters '(', ')' and '*'. A string entered is legitimate if
// Any left parenthesis '(' must have a corresponding right parenthesis ')'.
// right parenthesis ')' must have a corresponding left parenthesis '('.
// Left parenthesis '(' must go before the corresponding right parenthesis ')'.
// could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".

const std = @import("std");
const ValidChar = enum(u8) { open = '(', close = ')', asterisk = '*' };

fn validParenthesis(s: []const u8) !bool {
    if (s[0] == ')') return false;
    var min_open: i32 = 0;
    var max_open: i32 = 0;
    for (s) |value| {
        const ch = try std.meta.intToEnum(ValidChar, value);
        switch (ch) {
            .open => {
                min_open += 1;
                max_open += 1;
            },
            .close => {
                min_open -= 1;
                max_open -= 1;
            },
            .asterisk => {
                min_open -= 1;
                max_open += 1;
            },
        }
        if (max_open < 0) return false;
        if (min_open < 0) min_open = 0;
    }
    return (min_open == 0);
}

pub fn main() !void {
    const str = [_]u8{ '*', '(', '(', ')' };
    const result = try validParenthesis(&str);
    std.debug.print("{}", .{result});
}
