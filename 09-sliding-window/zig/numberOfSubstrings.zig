const std = @import("std");

fn createThreeCharEnum(charArr: [3]u8) !type {
    if (charArr.len < 3) return error.InvaildSize;
    return enum(u8) {
        first = charArr[0],
        second = charArr[1],
        third = charArr[2],
    };
}

// Given a string s consisting only of characters a, b and c.
// Return the number of substrings containing at least one occurrence of all these characters a, b and c.
// fn numberOfSubString(charArr: []const u8) !void {
//     var count: usize = 0;

//     for (charArr, 0..) |value, i| {}
// }

pub fn main() !void {
    const charEnum = try createThreeCharEnum(.{ 'a', 'b', 'c' });
    const charArr = [_]charEnum{ charEnum.second, charEnum.second, charEnum.first, charEnum.third, charEnum.third, charEnum.first };
    _ = charArr;
}
