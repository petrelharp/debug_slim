import tskit

ts = tskit.load("test.trees")

for var in ts.variants(isolated_as_missing=False):
    print(var)
    for k in ts.samples():
        geno = var.genotypes[k]
        msp_genotypes = var.alleles[geno].split(",")
        print("msp:", msp_genotypes)

