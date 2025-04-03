// SPDX-License-Identifier: MIT

pragma solidity 0.8.20;

import {HorseStore} from "../../src/horsestore/v1/HorseStore.sol" ;
import {Test, console2} from "forge-std/Test.sol";



abstract contract Base_TestV1 is Test {
    HorseStore public horseStore ;
    HorseStore public horseStore2 ;
   
   function setUp() public virtual  {
    horseStore = new HorseStore() ;
    
   }
   function testReadValue () public{
    uint256 initialValue = horseStore.readNumberOfHorses();

    assertEq(initialValue,0) ;
   }
   function testWriteValue (uint256 numberOfHorses) public {
    horseStore.updateHorseNumber(numberOfHorses);
    assertEq(horseStore.readNumberOfHorses(),numberOfHorses);
   }
}