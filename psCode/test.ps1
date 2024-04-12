function weightFunction {
    param (
        [int]$x
    )
    $result = 0
    while ($x) {
        $result += $x -band 1
        $x = $x -shr 1;  
    }   
    return $result; 
}
function F2 {
    param (
        [int]$n
    )
    $length = 1 -shl $n
    $trustable = New-Object byte[] $length
    for ($i = 0; $i -lt $length; $i++) {
        $w = weightFunction -x $i
        $trustable[$i] = ($w -band 1) -bxor 1
    }
    # Trả về mảng
    return $trustable
}
function F1 {
    param (
        [int]$n
    )
    $half_n = ($n + 1) -shr 1
    $length = 1 -shl $n
    $trustable = New-Object object[]  $length
    for ($i = 0; $i -lt $length; $i++) {
        $w = weightFunction -x $i
        if ($w -ge $half_n) {
            $trustable[$i] = 1
        }
        else {
            $trustable[$i] = 0
        }
    }
    # Trả về mảng
    return $trustable
}
# Gọi hàm F2 và lưu kết quả vào biến
$resultArray = F2 -n 3
# In kết quả
$resultArray