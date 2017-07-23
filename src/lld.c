//////////////////////////////////////////////////////////////////////////////////
// lld.c for Cosmos OpenSSD
// Copyright (c) 2014 Hanyang University ENC Lab.
// Contributed by Yong Ho Song <yhsong@enc.hanyang.ac.kr>
//                Gyeongyong Lee <gylee@enc.hanyang.ac.kr>
//     		 	  Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
//
// This file is part of Cosmos OpenSSD.
//
// Cosmos OpenSSD is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// Cosmos OpenSSD is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Cosmos OpenSSD; see the file COPYING.
// If not, see <http://www.gnu.org/licenses/>. 
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Company: ENC Lab. <http://enc.hanyang.ac.kr>
// Engineer: Gyeongyong Lee <gylee@enc.hanyang.ac.kr>
//     		 Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
// 
// Project Name: Cosmos OpenSSD
// Design Name: Greedy FTL
// Module Name: Low Level Driver
// File Name: lld.c
//
// Version: v1.0.3
//
// Description: 
//   - interface to NAND flash memory controller
//   - reset, mode change, status check
//   - erase, read, program
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Revision History:
//
// * v1.0.3
//   - replace bitwise operation with decimal operation
//
// * v1.0.2
//   - change in naming convention
//
// * v1.0.1
//   - add debugging print functions
//
// * v1.0.0
//   - First draft
//////////////////////////////////////////////////////////////////////////////////

#include "lld.h"

#include "xil_io.h"

#include "ftl.h"

#include "host_controller.h"

int SsdReset(u32 chNo, u32 wayNo)
{
	DebugPrint("<====Entering SsdReset====>\r\n");

  switch(chNo)
  {
    case 0:
      WriteCh0Command(wayNo, SSD_CMD_RESET);
      break;

    case 1:
      WriteCh1Command(wayNo, SSD_CMD_RESET);
      break;

    case 2:
      WriteCh2Command(wayNo, SSD_CMD_RESET);
      break;

    case 3:
      WriteCh3Command(wayNo, SSD_CMD_RESET);
      break;
  }

	DebugPrint("<====Leaving SsdReset====>\r\n");

  return 0;
}

int SsdModeChange(u32 chNo, u32 wayNo)
{
	DebugPrint("<====Entering SsdModeChange====>\r\n");

  switch(chNo)
  {
    case 0:
      WriteCh0Command(wayNo, SSD_CMD_MODE_CHANGE);
      break;

    case 1:
      WriteCh1Command(wayNo, SSD_CMD_MODE_CHANGE);
      break;

    case 2:
      WriteCh2Command(wayNo, SSD_CMD_MODE_CHANGE);
      break;

    case 3:
      WriteCh3Command(wayNo, SSD_CMD_MODE_CHANGE);
      break;
  }

	DebugPrint("<====Leaving SsdModeChange====>\r\n");

  return 0 ;
}

// bit number
//+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
//|31,23,15,7 |30,22,14,6 |29,21,13,5 |28,20,12,4 |27,19,11,3 |26,18,10,2 |25,17,9,1  |24,16,8,0  |
//+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+
//|
//|(0)protect | (0)busy   |  (0)busy  | (0)busy   |    '0'    |    '0'    | (0) pass  | (0) pass  |
//|(1)writable| (1)ready  |  (1)ready | (1)ready  |           |           | (1) fail  | (1) fail  |
//+-----------+-----------+-----------+-----------+-----------+-----------+-----------+-----------+

int SsdReadChWayStatus(u32 chNo, u32 wayNo)
{
	//xil_printf("<====Entering SsdReadChWayStatus====>\n");

  u32 chStatus = 0;
  u32 rbMask = 0;
  u32 errMask = 0;

  switch(chNo)
  {
    case 0:
      chStatus = ReadCh0WayStatus(wayNo);
      break;

    case 1:
      chStatus = ReadCh1WayStatus(wayNo);
      break;

    case 2:
      chStatus = ReadCh2WayStatus(wayNo);
      break;

    case 3:
      chStatus = ReadCh3WayStatus(wayNo);
      break;

    default:
      return 1;
      break;
  }

  rbMask  = WAY_RB_MASK;
  errMask = WAY_ERR_MASK;

  if((chStatus & rbMask) == rbMask)
  {
    if((chStatus & errMask) == 0)	// previous operation has passed!
      return 0;
    else	// previous operation has failed!
      return 1;
  }
  else	// previous operation is being executed; busy state
    return chStatus;
	//xil_printf("<====Leaving SsdReadChWayStatus====>\n");

}

int SsdBlockErase(u32 chNo, u32 wayNo, u32 rowAddr)
{
	//xil_printf("<====Entering SsdBlockErase====>\n");

  switch(chNo)
  {
    case 0:
      WriteCh0RowAddr(wayNo, rowAddr);
      WriteCh0Command(wayNo, SSD_CMD_ERASE);
      break;

    case 1:
      WriteCh1RowAddr(wayNo, rowAddr);
      WriteCh1Command(wayNo, SSD_CMD_ERASE);
      break;

    case 2:
      WriteCh2RowAddr(wayNo, rowAddr);
      WriteCh2Command(wayNo, SSD_CMD_ERASE);
      break;

    case 3:
      WriteCh3RowAddr(wayNo, rowAddr);
      WriteCh3Command(wayNo, SSD_CMD_ERASE);
      break;
  }

	//xil_printf("<====Leaving SsdBlockErase====>\n");

  return 0;
}

int SsdPageRead(u32 chNo, u32 wayNo, u32 rowAddr, u32 dstAddr)
{
	DebugPrint("<====Entering SsdPageRead====>\n");

  switch(chNo)
  {
    case 0:
      WriteCh0RowAddr(wayNo, rowAddr);
      WriteCh0MemAddr(wayNo, dstAddr);
      WriteCh0Command(wayNo, SSD_CMD_READ);
      break;

    case 1:
      WriteCh1RowAddr(wayNo, rowAddr);
      WriteCh1MemAddr(wayNo, dstAddr);
      WriteCh1Command(wayNo, SSD_CMD_READ);
      break;

    case 2:
      WriteCh2RowAddr(wayNo, rowAddr);
      WriteCh2MemAddr(wayNo, dstAddr);
      WriteCh2Command(wayNo, SSD_CMD_READ);
      break;

    case 3:
      WriteCh3RowAddr(wayNo, rowAddr);
      WriteCh3MemAddr(wayNo, dstAddr);
      WriteCh3Command(wayNo, SSD_CMD_READ);
      break;
  }

	DebugPrint("<====Leaving SsdPageRead====>\n");

  return 0;
}

int SsdPageProgram(u32 chNo, u32 wayNo, u32 rowAddr, u32 srcAddr)
{
	DebugPrint(">>>>>>>>>>>>>>>>>>>Entering SsdPageProgram<<<<<<<<<<<<<<<<<<<<<<<>\n");

  switch(chNo)
  {
    case 0:
      WriteCh0RowAddr(wayNo, rowAddr);
      WriteCh0MemAddr(wayNo, srcAddr);
      WriteCh0Command(wayNo, SSD_CMD_PROG);
      break;

    case 1:
      WriteCh1RowAddr(wayNo, rowAddr);
      WriteCh1MemAddr(wayNo, srcAddr);
      WriteCh1Command(wayNo, SSD_CMD_PROG);
      break;

    case 2:
      WriteCh2RowAddr(wayNo, rowAddr);
      WriteCh2MemAddr(wayNo, srcAddr);
      WriteCh2Command(wayNo, SSD_CMD_PROG);
      break;

    case 3:
      WriteCh3RowAddr(wayNo, rowAddr);
      WriteCh3MemAddr(wayNo, srcAddr);
      WriteCh3Command(wayNo, SSD_CMD_PROG);
      break;
  }

	DebugPrint("<====>>>>>>>>>>>>>>>>>>>>Entering SsdPageProgram<<<<<<<<<<<<<<<<====>\n");

  return 0;
}

int SsdErase(u32 chNo, u32 wayNo, u32 blockNo)
{
	//xil_printf("<====Entering SsdErase====>\n");

	return SsdBlockErase(chNo, wayNo, blockNo * PAGE_NUM_PER_BLOCK);

	//xil_printf("<====Leaving SsdErase====>\n");

}

int SsdRead(u32 chNo, u32 wayNo, u32 rowAddr, u32 dstAddr)
{
	DebugPrint("<====Entering SsdRead====>\n");

	return SsdPageRead(chNo, wayNo, rowAddr, dstAddr);

	DebugPrint("<====Leaving SsdRead====>\n");

}

int SsdProgram(u32 chNo, u32 wayNo, u32 rowAddr, u32 srcAddr)
{
	DebugPrint(">>>>>>>>>>>>>>>>>>Entering SsdPageProgram<<<<<<<<<<<<<<<<<\n");

	return SsdPageProgram(chNo, wayNo, rowAddr, srcAddr);


}

void WaitWayFree(u32 ch, u32 way)
{
	//DebugPrint("<====Entering WaitWayFree====>\n");

	for( ; ; )
	{
		if(0 == SsdReadChWayStatus(ch, way))
			break;
		else if(1 == SsdReadChWayStatus(ch, way))
		{
			switch(ch)
			{
			case 0:
				xil_printf("!!! a failure was detected in previous %8x operation - %d,%d!!!\r\n", readCmdCh0(way), ch, way);
				break;

			case 1:
				xil_printf("!!! a failure was detected in previous %8x operation - %d,%d!!!\r\n", readCmdCh1(way), ch, way);
				break;

			case 2:
				xil_printf("!!! a failure was detected in previous %8x operation - %d,%d!!!\r\n", readCmdCh2(way), ch, way);
				break;

			case 3:
				xil_printf("!!! a failure was detected in previous %8x operation - %d,%d!!!\r\n", readCmdCh3(way), ch, way);
				break;

			default:
				xil_printf("!!! invalid channel - %d,%d!!!\r\n", ch, way);
				break;
			}

			break;
		}
	}
	//DebugPrint("<====Leaving WaitWayFree====>\n");

}
