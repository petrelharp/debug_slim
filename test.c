#include <err.h>

#include <tskit.h>

#define EXIT_FAILURE -1

#define check_tsk_error(val)                                                            \
    if (val < 0) {                                                                      \
        errx(EXIT_FAILURE, "line %d: %s", __LINE__, tsk_strerror(val));                 \
    }

int
main(int argc, char **argv)
{
    int ret;
    tsk_treeseq_t ts;
    tsk_variant_t var;
    tsk_size_t s, j;
    tsk_id_t k;
    const tsk_id_t *samples;

    if (argc != 2) {
        errx(EXIT_FAILURE, "usage: <tree sequence file>");
    }
    ret = tsk_treeseq_load(&ts, argv[1], 0);
    check_tsk_error(ret);

    samples = tsk_treeseq_get_samples(&ts);

    ret = tsk_variant_init(&var, &ts, NULL, 0, NULL, TSK_ISOLATED_NOT_MISSING);
    check_tsk_error(ret);

    for (s = 0; s < tsk_treeseq_get_num_sites(&ts); s++) {
        ret = tsk_variant_decode(&var, (tsk_id_t) s, 0);
        check_tsk_error(ret);
        tsk_variant_print_state(&var, stdout);
        for (j = 0; j < tsk_treeseq_get_num_samples(&ts); j++) {
            k = var.genotypes[j];
            printf("\t%d\t%d: '%.*s'\n", samples[j], k, (int) var.allele_lengths[k],
                    var.alleles[k]);
        }
    }

    tsk_variant_free(&var);
    tsk_treeseq_free(&ts);
    return 0;
}
