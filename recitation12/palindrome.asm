.data
inputStr: .asciiz "racecar"

.text
.globl main

main:
    la $t0, inputStr          # left pointer
    la $t1, inputStr          # right pointer (start)
    
find_end:
    lb $t2, 0($t1)
    beq $t2, $zero, found_end
    addi $t1, $t1, 1
    j find_end

found_end:
    addi $t1, $t1, -1        # last valid character
    
    move $a0, $t0            # left address
    move $a1, $t1            # right address
    
    jal isPalindrome
    
    # Print result (1 for true, 0 for false)
    move $a0, $v0
    li $v0, 1
    syscall
    
    li $v0, 10               # exit
    syscall
    
isPalindrome:
    # Base case: if left >= right, return true
    bge $a0, $a1, return_true
    
    # Load characters at left and right pointers
    lb $t0, 0($a0)
    lb $t1, 0($a1)
    
    # If characters don't match, return false
    bne $t0, $t1, return_false
    
    # Save return address
    addi $sp, $sp, -4
    sw $ra, 0($sp)
    
    # Move pointers inward and recurse
    addi $a0, $a0, 1
    addi $a1, $a1, -1
    jal isPalindrome
    
    # Restore and return
    lw $ra, 0($sp)
    addi $sp, $sp, 4
    jr $ra

return_true:
    li $v0, 1
    jr $ra

return_false:
    li $v0, 0
    jr $ra