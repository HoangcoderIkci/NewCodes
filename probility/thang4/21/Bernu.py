from scipy.stats import binom

# Parameters for the binomial distribution
n = 100  # Number of trials
p = 0.25  # Probability of success in each trial

# Create a binomial distribution with parameters n and p
binom_dist = binom(n, p)

# Sample from the binomial distribution
sample = binom_dist.rvs(size=10)  # Randomly sample 10 times

# Print the sample from the binomial distribution
print("Sample from the binomial distribution:", sample)

# Calculate the mean of the binomial distribution
mean = binom_dist.mean()
print("Mean of the binomial distribution:", mean)

# Calculate the variance of the binomial distribution
variance = binom_dist.var()
print("Variance of the binomial distribution:", variance)

# Calculate the probability of a specific number of successes (k) in the binomial distribution
k = 3  # Number of successes
probability_k = binom_dist.pmf(k)
print(f"Probability of k={k} successes in the binomial distribution:", probability_k)
