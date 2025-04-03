// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220b988c607a85383f8199074fd31c60e96cb04e124d820a7476f812d5c5d66788d64736f6c63430008140033

// the bytecode above contain 3 sections : 
// 1 - Contract creation 
// 2 - Runttime 
// 3 - Metadata 

// 1 - Contract Creation Code :

// Free Memory Pointier
PUSH1 0x80              //[ 0x80 ]
PUSH1 0x40              //[ 0x40 , 0x80 ]
MSTORE                  // []                      Memory : slot(2) [0x40] = 0x80  (free memory pointer)

// if someone don't send value wiht constructer jumb to 0x0e Pc/jumpDest .
// if send value Revert .
CALLVALUE               // [msg.sender value ex(0,20,... in wei)]
DUP1                    // [mgs.sender , msg.sender]
//it pop msg.sender :check if msg.sender is zero push 1 else push 0
ISZERO                  //  [msg.sender == 0, msg.sender]
PUSH1 0x0e              //  [0x0e ,msg.sender == 0, msg.sender]
JUMPI                   //[msg.sender]
PUSH0                   //[0,msg.sender]
DUP1                    //[ 0,0,msg.sender ]
REVERT                  // [msg.sender]    Stop exe .

// it stick the runtime code on chain :
JUMPDEST
POP                    // []
PUSH1 0xa5             // [0xa5]
DUP1                   // [ 0xa5 , 0xa5]
PUSH2 0x001b           // [  0x001b, 0xa5 , 0xa5, ]
PUSH0                  // [ 0,0x001b , 0xa5 , 0xa5 ]
CODECOPY               // [0xa5] memory :[runtime code : start from 0x001b  and go 0xa5 (165) bytes]
PUSH0                  // [0x00 , 0xa5]
//[it take the index to start then the size , it return all bytes from index uint the size end.
// in our code it return from index 0 in memory to index 165 (0xa5)]
RETURN                 //[]
INVALID                //[]

// 2. Runtime code 
// Entry point of all calls 

//Free memory pointer 
PUSH1 0x80          
PUSH1 0x40
MSTORE

// Checking for msg.value  ,if it given , revert 
CALLVALUE           // [ msg.value ]
DUP1                // [ msg.value , msg.value ]
ISZERO              // [msg.valu==0 , msg.value]
PUSH1 0x0e          // [0x0e ,msg.valu==0 , msg.value]
JUMPI               // [msg.value]
// jump to "continue !"" if msg.value == 0 
PUSH0               // [ 0x00, msg.value]
DUP1                 // [0x00, 0x00, msg.value]
REVERT

// if  msg.value == 0 ,start here 
// continue !

JUMPDEST            // [msg.value]
POP                // []

//this for checking if there is enough calldata for a function selector (>4bytes)

PUSH1 0x04        // [0x04]
CALLDATASIZE      // [ CallDataSize , 0x04 ]
LT               //[ CallDataSize < 0x04]
PUSH1 0x30      // [  0x30 , CallDataSize < 0x04 ]
JUMPI           //[]
// if calldata < 0x04 bytes  -> callData_jump 


// Function Dispatching in solidity 

PUSH0               // [0]
CALLDATALOAD        // [calldata (only 32bytes strat from index 0 cause we push 0) ]
PUSH1 0xe0          // [ 0xe0 , calldata ]
SHR                 // [ calldata [0 :4] ]   function selector 

// Function Dispatching for update_number_of_Horses

DUP1                // [ func_selector , func_selector ]
PUSH4 0xcdfead2e    // [ 0xcdfead2e , func_selector , func_selector ]
EQ                  // [ func_selector = 0xcdfead2e ,func_selector ]
PUSH1 0x34         // [ 0x34, func_selector = 0xcdfead2e ,func_selector ]
JUMPI               // [ func_selector ]
// if func_selector = 0xcdfead2e -> set_number_of_Horses to jump dest 1 

// Function Dispatching for Read_number_of_horses

DUP1                // [ func_selector , func_selector ]         //in our Huff code we remove this , our is more gas optimaze !
PUSH4 0xe026c017    // [ 0xe026c017 ,func_selector , func_selector ] 
EQ                 //  [ func_selector == 0xe026c017, func_selector ] 
PUSH1 0x45        //   [ 0x45 , func_selector == 0xe026c017, func_selector ]
JUMPI             // [func_selector]
//If func_selector= 0xe026c017 -> get_number_of_horses


// callData_jump
// revert Jumpset
JUMPDEST        // []
// we push two zeros cause revert need it for input (if we have revert message )
PUSH0           //[0]
DUP1            //[0 , 0]
REVERT          //[]

// updateHorseNumber - jump dest 1 
// Setup jumping program counter in the stack 
PUSH1 0x43          //[ 0x43 func_selector, ]
PUSH1 0x3f         //[ 0x3f ,0x43 ,func_selector ]
CALLDATASIZE      //[ CALLDATASIZE  ,0x3f ,0x43 ,func_selector ]
PUSH1 0x04       // [ 0x04 ,CALLDATASIZE  ,0x3f ,0x43 ,func_selector ]
PUSH1 0x59      // [0x59 , 0x04 ,CALLDATASIZE  ,0x3f ,0x43 ,func_selector ]
// it jump to 0x59 for updateHorseeNumber 
JUMP        // [ 0x04 ,CALLDATASIZE  ,0x3f ,0x43 ,func_selector ]

// updateHorseNumber jump dest 4
// we can finally run an sstore to save our value to store : 
// 1. Function dispatch 
// 2. checked msg.value 
// 3. checked that calldata is long enough 
// 4 . receive the  the number from calldata for use 
JUMPDEST    // [ calldata(numberToUpdate(parameter)) , 0x43 , func_selector]
PUSH0       // [ 0 , calldata(numberToUpdate(parameter)) , 0x43 , func_selector]
SSTORE      // [0x43, func_selector]    storage slot (0) = calldata(numbertoUpadate)
// jumpt to 0x43 offset .
JUMP        // [func_selector]

// updateHorseNumber jumb dest 5 at 0x43
JUMPDEST      // [func_selector]
STOP          // [func_selector]

//readNumberOfHorses jumpdest 1 (only one )

JUMPDEST      // [func_selector]
PUSH0         // [0,func_selector]
SLOAD         // [slot(0) value (numOfHorses) ,func_selector]
PUSH1 0x40    // [0x40 ,slot(0) value(numOfHorses) ,func_selector]
MLOAD         // [0x80,slot(0) value(numOfHorses) ,func_selector]   //Memory [0x40 :0x80] (free memory pointer)
SWAP1        // [slot(0) value(numOfHorses) ,0x80, ,func_selector]
DUP2         // [0x80 ,slot(0) value(numOfHorses) ,  ,0x80, ,func_selector]
MSTORE       // [0x80, ,func_selector]      // Memory [0x80 : slot(0) value(numOfHorses)]
// we need to updadte the free memory pointer at location (0x40) to point from 0x80 to the next 32 byte slot But the soldity smart
// enongh the know that we don't need it anymore cause the call will end so we don't update the free memory pointer .
PUSH1 0x20   // [0x20 , 0x80, ,func_selector]
ADD         // [0xa0,func_selector]             // we move to the next slot in memory so we add 0x20 (32 bytes)
PUSH1 0x40  // [0x40 ,0xa0,func_selector] 
MLOAD      // [0x80,0xa0,func_selector]
DUP1       // [0x80, 0x80 ,0xa0,func_selector]
SWAP2      // [ 0xa0, 0x80 ,0x80 ,func_selector]
SUB       // [ 0xa0 - 0x80 = 0x20(size ) ,0x80 ,func_selector]
SWAP1     //  [ 0x80 , 0xa0 - 0x80 = 0x20(size ) ,func_selector]
// Return the value of 32 bytes that is  located at 0x80 in Memory 
RETURN   //[func_selector]

// updateHorseNumber jump dest 2 
// check if there is a  value to update the horse number 
// 4 bytes for function selector , 32 bytes for horse number (uint256 parameter)
JUMPDEST          // [ 0x04 ,CALLDATASIZE  ,0x3f ,0x43 ,func_selector ]
PUSH0             // [ 0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43 ,func_selector ]
PUSH1 0x20      // [0x20 , 0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector ]
DUP3             // [0x04 ,0x20 , 0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector ]
DUP5             // [CALLDATASIZE ,0x04 ,0x20 , 0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector ]
SUB              // [ CALLDATASIZE - 0x04 ,0x20 , 0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector ]
// is calldata have less data than func_selector puls 32 bytes ?
SLT             // [ CALLDATASIZE - 0x04 < 0x20 , 0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector ]
ISZERO          // [CALLDATASIZE - 0x04 < 0x20 ==false/true(if false iszero =1),0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector ]
PUSH1 0x68      // [0x68 ,more/equal data than selector puls 32,0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector ]
JUMPI           // [0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector]
// we will jump to jump dest 3 if call data have more : (CALLDATASIZE - 0x04 < 0x20 ==false) give 0 which make izero = 1 which let jump
// func_selector + 0x20 (32 bytes) .

// Revert if there isn't enough calldata 
PUSH0           // [ 0 , 0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector]
DUP1            // [ 0 , 0 ,0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector]
REVERT

// updateHorseNumber jump dest 3 
JUMPDEST     /// [0x00 ,0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector]
POP         // [ 0x04 ,CALLDATASIZE  ,0x3f ,0x43,func_selector]
// Ignore the first 4 bytes (function selector) then grab the rest from index 4 into the stack 
CALLDATALOAD    // [ calldata(numberToUpdate(parameter)) ,CALLDATASIZE  ,0x3f ,0x43,func_selector]
SWAP2           // [ 0x3f  ,CALLDATASIZE  ,calldata(numberToUpdate(parameter)) , 0x43 , func_selector]
SWAP1          // // [ CALLDATASIZE ,0x3f  ,  ,calldata(numberToUpdate(parameter)) , 0x43 , func_selector]
POP           // [ 0x3f ,calldata(numberToUpdate(parameter)) , 0x43 , func_selector]
// jump to dest 4 , 0x3f
JUMP          // [ calldata(numberToUpdate(parameter)) , 0x43 , func_selector]


// 3. Metadata , it not reached by any tx that try to interact with contract , ex :
// it is just for etherscan to verfiy,knowing version of solidty ,etc..
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
DUP9
INVALID
SMOD
INVALID
MSTORE8
DUP4
INVALID
NOT
SWAP1
PUSH21 0xfd31c60e96cb04e124d820a7476f812d5c5d66788d
PUSH5 0x736f6c6343
STOP
ADDMOD
EQ
STOP
CALLER


// see https://app.dedaub.com/decompile for decompile 
//https://github.com/Jon-Becker/heimdall-rs