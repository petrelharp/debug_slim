import tskit

ts = tskit.load("test.trees")

x = 0
for var in ts.variants(isolated_as_missing=False):
    for k in ts.samples():
        geno = var.genotypes[k]
        msp_genotypes = var.alleles[geno].split(",")
        # print("msp:", msp_genotypes)
        x += len(msp_genotypes)

print("Done: " + x)
