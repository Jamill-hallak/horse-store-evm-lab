object "HorseStoreYul" {

    code {

        // creation code , : copy the runtime code on the slot 0 in memory : huff do that auto .
        datacopy(0,dataoffset("runtime"),datasize("runtime"))
        return (0,datasize("runtime"))
    }
    object "runtime"{
        code{

            switch selector ()
            // updateHorseNumber
           case 0xcdfead2e {
           storeNumber(decodeAsUint(0))
        
        }
          // readNumberOfHorses
           case 0xe026c017 {
                returnUint(readNumber())
        }
        default {
            revert(0,0)
        }
        function storeNumber(newnumber){
            sstore(0,newnumber)
        }
        function readNumber() -> storedNumber {
            storedNumber := sload(0)
        }
        /* -- decoding functions -- */
        

         function selector() -> s {
           s := div(calldataload(0),0x100000000000000000000000000000000000000000000000000000000)
         }

            function decodeAsUint(offset) -> v {
            let positionInCalldata := add(4, mul(offset, 0x20))
            if lt(calldatasize(), add(positionInCalldata, 0x20)){
                revert(0, 0)
            }

            v := calldataload(positionInCalldata)
        }
        
        function returnUint(v){
            mstore(0,v)
            return(0,0x20)
        } 
        }
    }
}