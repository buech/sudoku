!subroutine print_board(board)
!   implicit none
!   integer, dimension(81), intent(in) :: board
!
!   print "(3 (' ', 3 i2))", board(1:27)
!   print *
!   print "(3 (' ', 3 i2))", board(28:54)
!   print *
!   print "(3 (' ', 3 i2))", board(55:81)
!   print *
!
!end subroutine

subroutine print_board(board)
   implicit none
   integer, dimension(81), intent(in) :: board

   print "(81 i0)", board

end subroutine

recursive function search(board, pos) result(res)
   implicit none
   integer, dimension(0:80) :: board
   integer, intent(in) :: pos
   logical :: res

   integer :: row, col, i, j, a, b
   logical, dimension(9) :: valid
   !integer :: invalid

   if(pos == 81) then
      res = .true.
      return
   end if

   if(board(pos) /= 0) then
      res = search(board, pos+1)
      return
   end if

   col = mod(pos, 9)
   row = pos / 9
   valid = .true.
   !invalid = 0

   do i=0,8
      a = board(9 * row + i)
      b = board(9 * i + col)
      if(a /= 0) then
         valid(a) = .false.
      end if
      if(b /= 0) then
         valid(b) = .false.
      end if
      !invalid = ior(invalid, ishft(1, board(9 * row + i)))
      !invalid = ior(invalid, ishft(1, board(9 * i + col)))
   end do

   col = col / 3 * 3
   row = row / 3 * 3

   do i=row,row+2
      do j=col,col+2
         a = board(9 * i + j)
         if(a /= 0) then
            valid(a) = .false.
         end if
         !invalid = ior(invalid, ishft(1, board(9 * i + j)))
      end do
   end do

   !invalid = ishft(invalid, -1)

   do i=1,9
      if(valid(i)) then
      !if(iand(invalid, 1) == 0) then
         board(pos) = i
         !call print_board(board)
         !print *
         !call sleep(1)
         if(search(board, pos+1)) then
            res = .true.
            return
         end if
      end if
      !invalid = ishft(invalid, -1)
   end do

   board(pos) = 0
   res = .false.

end function

subroutine usage(program_name)
   implicit none
   character(len=*), intent(in) :: program_name

   print *, "usage ", trim(program_name), " [-h] SUDOKU"
   print *
   print *, "Sudoku solver in Fortran 90 using backtracking"
   print *
   print *, "positional arguments:"
   print *, "  SUDOKU        Sudoku in the form of a continuous string read from"
   print *, "                left to right with 0 for empty cells, must have a"
   print *, "                length of at least 81 characters, additional"
   print *, "                characters are ignored"
   print *, "optional arguments:"
   print *, "  -h, --help    show this help message and exit"

end subroutine

program solver
   implicit none

   integer, dimension(81) :: board
   character(len=81) :: arg
   character(len=32) :: program_name
   integer :: i
   interface
      recursive function search(board, pos) result(res)
         integer, dimension(0:80) :: board
         integer, intent(in) :: pos
         logical :: res
      end function
   end interface

   call get_command_argument(0, program_name)

   if(command_argument_count() == 1) then
      call get_command_argument(1, arg)
      if(arg == "-h" .or. arg == "--help") then
         call usage(program_name)
         stop
      else
         if(len_trim(arg) < 81) then
            print *, "Error: The sudoku has too few fields"
            call usage(program_name)
            stop 1
         else
            do i=1,81
               read(arg(i:i),*) board(i)
            end do
         end if
      end if
   else if(command_argument_count() > 1) then
      print *, "Error: Too many arguments"
      call usage(program_name)
      stop 1
   else
      print *, "Error: Too few arguments"
      call usage(program_name)
      stop 1
   end if

   !print *, "Input:"
   !call print_board(board)

   if(search(board, 0)) then
      !print *, "Solution:"
      call print_board(board)
   else
      print *, "The puzzle is not solvable!"
   end if

end program
