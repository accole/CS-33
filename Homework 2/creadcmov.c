//Adam Cole

/*
  this function doesn't work because when the
  pointer is dereferenced it points to the null
  pointer, causing an error

long cread(long *xp){
   return (xp ? xp[-1] : -1);
}

  therefore we must rewrite it as cread_alt in
  order to execute the correct implementation,
  since we must use  a conditional move instead 
  of a jump instruction
*/
long j = -1;
long cread_alt(long *xp){
  long* u = &j;
  return *( !xp ? (xp-1) : u);
}
