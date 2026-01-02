# Bash script to run all selections with their respective plots.
snakemake --cores 10 --config selection=Ds # will run both "3pi" and "Ds"
snakemake --cores 10 --config selection=Bs
snakemake --cores 10 --config selection=BdNorm # will run both "BsNorm" and "BdNorm"
snakemake --cores 10 --config selection=plots
