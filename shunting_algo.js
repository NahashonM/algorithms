var fn = 'sin(max(2,3)/3*pi)'
var fn = '3+4*2/(1-5)**2**3'
var fn = '3-4+5'
fn = fn.replaceAll(/\s/g, '');

var ostack = []
var fstack = []

var precedence = { '**':4 , '/':3 , '*':3 , '+':1 , '-':0  }
var numRegEx = /\d+\.?\d*|t/g
var opRegEx = /\+|\-|\/|\*\*|\*|\(|\)/g
var fnRegEx = /[A-Za-z]+/g

var numIndex = 0
var opIndex = 0
var fnIndex = 0


for (let i = 0; i < fn.length; i++) {

  numRegEx.lastIndex = numIndex
  opRegEx.lastIndex = opIndex
  fnRegEx.lastIndex = fnIndex

  let match = numRegEx.exec(fn)

  // Token is a number
  if (match && match.index === i) {
    let matched_number = match.toString()
    ostack.push(matched_number)
    numIndex = i + matched_number.length
    continue
  }

  // Token is a function
  if ((match = fnRegEx.exec(fn)) && match.index === i) {
    let matched_fn = match.toString()
    fnIndex = i + matched_fn.length
    fstack.push(matched_fn)
    continue
  }

  // Token is an operator
  if ((match = opRegEx.exec(fn)) && match.index === i) {
    let matched_op = match.toString()
    opIndex = i + matched_op.length

    if (fstack.length > 0) {

      let fstack_index = fstack.length - 1
      let matched_prec = precedence[matched_op];
      let last_OpPrec = precedence[fstack[fstack_index]];
      
      if (matched_op === ")") { // find matching paranthesis and remove it

        // 3,4,+,5,-

        for (let j = fstack.length - 1; j >= 0; j--) { // Pop stack until ( is at top of stack

          let st_temp = fstack.pop()
          if (st_temp === '(') {														// discard matching parenthisis
            
             console.log("dd= " + st_temp + " fs= " + fstack)
            
            if( (j-1) > 0 && !precedence[fstack[j-1]])		// pop functions from stack
            { 
              ostack.push(fstack.pop()) 
              j--
            }
            
            
            break
          }
          
          ostack.push(st_temp)
        }


      } else if (matched_prec && last_OpPrec && last_OpPrec >= matched_prec) {
        
        // test associativity
        if(matched_op !== "**")
          ostack.push(fstack.pop()) // pop higher/equal precedence reft associative operator into output
        
        fstack.push(matched_op) // push lower / equal precedence to operator stack

      } else {

        fstack.push(matched_op) // push new operator to stack

      }

    } else {
      fstack.push(matched_op)
    }

  }
  // Done processing token

}

// pop all remaining operators
for (let j = fstack.length - 1; j >= 0; j--) {

  ostack.push(fstack.pop())
}




console.log(fstack.toString())
console.log(ostack.toString())

console.log("done")