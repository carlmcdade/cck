<?php

	/*
	table v.1.0.0b
	Class for easy composing of complex tables
	By Llorenç Herrera [lha@hexoplastia.com]
	Please do not remove this credits
	*/

	class common_table
	{
		var $content;
		var $colspan = 0;
		var $style = "table_cell";
		var $highlight;
		var $highlight_class = "table_highlighted";
		var $nobr = false;
		
		function table_cell ($content, $colspan, $style, $highlight, $nobr)
		{
			$this->content = $content;
			if ($colspan != "") $this->colspan = $colspan;
			if ($style != "") $this->style = $style;
			$this->nobr = $nobr;
			$this->highlight = $highlight;
		}
		
		function gettd ()
		{
			$retr .= "<td class=\"".$this->style."\"".($this->colspan != 0 ? " colspan=".$this->colspan : "").">";
			$retr .= $this->getcontent ();
			$retr .= "</td>";
			return $retr;
		}
		
		function getcontent ()
		{
			$retr = ($this->highlight != "" ? $this->highlight ($this->content, $this->highlight) : $this->returnisnobr ());
			return $retr;
		}
		
		function returnisnobr ()
		{
			return ($this->nobr ? str_replace (" ", "&nbsp;", $this->content) : $this->content);
		}
		
		function highlight ($string, $tohighlight)
		{
			return str_replace ($tohighlight, "<span class=\"".$this->highlight_class."\">".$tohighlight."</span>", $string);
		}
	}
	
	class table_row
	{
		var $cells;
		var $style = "table_row";
		
		function table_row ($cells, $style)
		{
			$this->cells = $cells;
			if ($style != "") $this->style = $style;
		}
		
		function addcell ($cell)
		{
			$this->cells[] = $cell;
		}
		
		function gettr ()
		{
			$retr .= "<tr class=\"".$this->style."\">";
			while (list (, $cell) = each ($this->cells))
				$retr .= $cell->gettd ();
			$retr .= "</tr>";
			return $retr;
		}
	}
	
	class table
	{
		var $width = "100%";
		var $style = "table_style";
		var $cellpadding = 3;
		var $cellspacing = 1;
		var $alternatecolors = true;
		var $rowstyles = array ("table_row1", "table_row2");
		var $rowstyles_counter = 0;
		var $rows;
		
		function table ($width, $style, $cellpadding, $cellspacing)
		{
			if ($width != "") $this->width = $width;
			if ($style != "") $this->style = $style;
			if ($cellpadding != "") $this->cellpadding = $cellpadding;
			if ($cellspacing != "") $this->cellspacing = $cellspacing;
		}
		
		function addrow ($row)
		{
			$this->rows[] = $row;
		}
		
		function get ()
		{
			$retr .= "<table border=0 width=\"".$this->width."\" cellpadding=".$this->cellpadding." cellspacing=".$this->cellspacing." style=\"".$this->style."\">";
			while (list (, $row) = each ($this->rows))
			{
				if ($this->alternatecolors)
				{
					$row->style = $this->rowstyles [$this->rowstyles_counter];
					$this->rowstyles_counter ++;
					if ($this->rowstyles_counter >= sizeof ($this->rowstyles))
						$this->rowstyles_counter = 0;
				}
				$retr .= $row->gettr ();
			}
			$retr .= "</table>";
			return $retr;
		}
		
		function dump ()
		{
			echo $this->get ();
		}
	}

?>