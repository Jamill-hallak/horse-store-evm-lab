pragma solidity 0.8.20;

import {Base_TestV1,HorseStore} from "./Base_TestV1.t.sol";
import {HorseStoreYul} from "../../src/horsestore/v1/HorseStoreYul.sol";
import {Test, console} from "forge-std/Test.sol";

contract HorseStoreYultest is Base_TestV1 {
//ToDo try optimaztion 2000  
bytes yulCode = hex"603680600a5f395ff3fe5f803560e01c8063cdfead2e1460245763e026c01714601b5780fd5b80602091548152f35b50602436106033576004359055005b80fd";
    function setUp() public override{
         horseStore = HorseStore( address (deployYul(yulCode))) ;
    }

    function deployYul(bytes memory code) internal returns (address deployedAddress) {
    assembly {
        // Skip the first 32 bytes (length) to get the actual code pointer.
        deployedAddress := create(0, add(code, 0x20), mload(code))
        // Revert if deployment fails.
        if iszero(deployedAddress) {
            revert(0, 0)
        }
    }
    console.log("address",deployedAddress) ;
}

}