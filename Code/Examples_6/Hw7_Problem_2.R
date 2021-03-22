#Apply the ratio method to sample from Beta (??,??) with ??=??=2>0.  You may do this in R if you want (just not with rbeta()).  

beta_func <- function(n, count = 1){
  result <- c(0)
  
  while(n > length(result)){
    s <- runif(1)
    t <- runif(1)
    kv <- 3 * ((3^(1/2))/16)
    ku <- 0.5 
    numerator <- (kv * t)
    denominator <- (ku * s)
    x <- numerator / denominator # X = V/U has distribution f(x)
    
    if(0 >= (x*x) - x){
      if(sqrt(x - x*x) >= (denominator)){
        result[count] <- x
        count <- count + 1
      }
    }
  }
  return(result)
}


compare_func <- function(n){
  rbeta(n, 2, 2) 
}



final_output <- beta_func(100000)
compare_rbeta <- compare_func(100000)


plot(density(final_output), col=rgb(0.8,0.4,0.1,0.7), pch = 17)
lines(density(compare_rbeta), col=rgb(0.2,0.4,0.1,0.7), pch = 17)
legend(x = "center", legend = c("result", "rbeta"), col = c(rgb(0.8,0.4,0.1,0.7), rgb(0.2,0.4,0.1,0.7)), pch = c(17, 17))
