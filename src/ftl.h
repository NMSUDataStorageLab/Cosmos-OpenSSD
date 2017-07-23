//////////////////////////////////////////////////////////////////////////////////
// ftl.h for Cosmos OpenSSD
// Copyright (c) 2014 Hanyang University ENC Lab.
// Contributed by Yong Ho Song <yhsong@enc.hanyang.ac.kr>
//                Gyeongyong Lee <gylee@enc.hanyang.ac.kr>
//				  Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
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
//			 Jaewook Kwak <jwkwak@enc.hanyang.ac.kr>
//
// Project Name: Cosmos OpenSSD
// Design Name: Greedy FTL
// Module Name: Flash Translation Layer
// File Name: ftl.h
//
// Version: v1.0.2
//
// Description:
//   - define NAND flash memory and SSD parameters
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// Revision History:
//
// * v1.0.2
//   - add constant to calculate ssd size
//
// * v1.0.1
//   - replace bitwise operation with decimal operation
//
// * v1.0.0
//   - First draft
//////////////////////////////////////////////////////////////////////////////////

#ifndef	FTL_H_
#define	FTL_H_

#define	SECTOR_SIZE_FTL			512

#define	PAGE_SIZE				8192  													// 8KB
#define	PAGE_NUM_PER_BLOCK		256														// 256 pages per block
#define	BLOCK_NUM_PER_DIE		4096 													// Each Die has 4096 blocks
#define	BLOCK_SIZE_MB			((PAGE_SIZE * PAGE_NUM_PER_BLOCK) / (1024 * 1024))		// 2097152/1048576 = 2 MB

#define	CHANNEL_NUM				4 														// Total 4 channels
#define	WAY_NUM					4 														// Each channel has 4 ways
#define	DIE_NUM					(CHANNEL_NUM * WAY_NUM) 								// 4*4=16 Each Die is connected with each way

#define	SECTOR_NUM_PER_PAGE		(PAGE_SIZE / SECTOR_SIZE_FTL) 							// 8192/512  = 16

#define	PAGE_NUM_PER_DIE		(PAGE_NUM_PER_BLOCK * BLOCK_NUM_PER_DIE) 				// 256*4096 = 1048576
#define	PAGE_NUM_PER_CHANNEL	(PAGE_NUM_PER_DIE * WAY_NUM) 							// 1048576*4 = 4194304
#define	PAGE_NUM_PER_SSD		(PAGE_NUM_PER_CHANNEL * CHANNEL_NUM)					// 4194304*4 = 16777216

#define	BLOCK_NUM_PER_CHANNEL	(BLOCK_NUM_PER_DIE * WAY_NUM)							// 4096*4 = 16384
#define	BLOCK_NUM_PER_SSD		(BLOCK_NUM_PER_CHANNEL * CHANNEL_NUM)					// 16384*4 = 65536

#define SSD_SIZE				(BLOCK_NUM_PER_SSD * BLOCK_SIZE_MB) 					// 65536*2 = 131072 MB
#define FREE_BLOCK_SIZE			(DIE_NUM * BLOCK_SIZE_MB)								// 16*2 = 32 MB
#define METADATA_BLOCK_SIZE		(1 * BLOCK_SIZE_MB)										// 1*2 = 2 MB

void InitNandReset();
void InitFtlMapTable();

#endif /* FTL_H_ */
