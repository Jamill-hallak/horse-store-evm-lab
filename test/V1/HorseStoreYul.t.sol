pragma solidity 0.8.20;

import {Base_TestV1,HorseStore} from "./Base_TestV1.t.sol";
import {HorseStoreYul} from "../../src/horsestore/v1/HorseStoreYul.sol";
contract HorseStoreYultest is Base_TestV1 {

    function setUp() public override{
         horseStore = HorseStore( address (new HorseStoreYul())) ;
    }
    
}