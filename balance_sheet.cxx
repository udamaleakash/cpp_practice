	if (!rtype)
	{
		if (validate::double_cmp(TRAN_AMT, total1, total2) != 0)
		{
			rprintf(rep, "\r\n\r\t\t\t\t\t\t\t ************* Untallied *********"
						 "****\r\n");
			if (excel)
				set_excel(excel, (char *)"**** Untallied *****");
			if (html)
				html->add_h("&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;**** Untallied *****", 4, 0);
			if (*printtyp == 4 && fp)
			{
				sprintf(psvbf, "TR_1 col_merge[6]<h> Untallied by :&emsp; %'.2lf|||||</h>\r\n", total1 - total2);
				fwrite(psvbf, 1, strlen(psvbf), fp);
			}
		}
		else if (*printtyp == 4 && (*bank_parameters.bank_type == 'B')) /* Web pdf - Balance Sheet & PL */
		{
			if (validate::double_cmp(TRAN_AMT, *depo_total, 0.0) != 0)
			{
				sprintf(psvbf, "TR_1 col_merge[6] C.D Ratio :&emsp; %'.2lf|||||\r\n", (*loan_total / *depo_total) * 100);
				fwrite(psvbf, 1, strlen(psvbf), fp);
			}
		}
	}
