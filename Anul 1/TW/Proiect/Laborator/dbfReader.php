<?php

class dbf
{
	public $nRecords;
	
	private $link;
	private $rStart;
	private $rSize;
	private $nFields;
	private $fieldName = array();
	private $fieldSize = array();
	private $fieldPos = array();
	
	private function getFieldID($name)
	{
		for($i = 0; $i < $this->nFields; $i++)
		{
			if($this->fieldName[$i] === $name) return $i;
		}
		return false;
	}

	
	public function __construct($flink)
	{
		$this->link = fopen($flink, "rb");
		$buffer = fread($this->link, 32);
		$this->nRecords = ord($buffer[4]) + ord($buffer[5]) * 256 + ord($buffer[6]) * 256 * 256 + ord($buffer[7]) * 256 * 256 * 256;
		$this->rStart = ord($buffer[8]) + ord($buffer[9]) * 256;
		$this->rSize = ord($buffer[10]) + ord($buffer[11]) * 256;
		$this->nFields = ($this->rStart - 264) / 32 - 1;
		//echo "Records: " . $this->nRecords . "<br>Start: " . $this->rStart . "<br>rSize: " . $this->rSize . "<br>Fields: " . $this->nFields . "<br>"; 
		for($i = 0; $i < $this->nFields; $i++)
		{
			fseek($this->link, 32 + 32 * $i, SEEK_SET);
			$buffer = fread($this->link, 32);
			array_push($this->fieldName, trim(substr($buffer, 0, 10). " "));
			array_push($this->fieldSize, ord($buffer[16]));
			$fpos = ord($buffer[12]) + ord($buffer[13]) * 256 + ord($buffer[14]) * 256 * 256 + ord($buffer[15]) * 256 * 256 * 256;
			array_push($this->fieldPos, $fpos);
		//	echo end($this->fieldName) . " " . end($this->fieldSize) . " " . end($this->fieldPos) . "<br>";
		}
	}
	public function __destruct()
	{
	}
	
	public function getRecord($fieldName, $fieldValue)
	{
		$nameID = $this->getFieldID($fieldName);
		for($i = $this->rStart; $i < $this->nRecords * $this->rSize; $i += $this->rSize)
		{
			fseek($this->link, $i, SEEK_SET);
			$deleted = fread($this->link, 2);
			if($deleted[0] == '*')
			{
				continue;
			}
			fseek($this->link, $i + $this->fieldPos[$nameID] , SEEK_SET);
			$buffer = fread($this->link, $this->fieldSize[$nameID]);
			if(rtrim(ltrim($buffer, " "), " ") === $fieldValue)
			{
				return ($i - $this->rStart) / $this->rSize;
			}
			
		}
		return false;
	}
	
	public function getMultipleRecords($fieldName, $fieldValue)
	{
		$nameID = $this->getFieldID($fieldName);
		$ret = array();
		for($i = $this->rStart; $i < $this->nRecords * $this->rSize; $i += $this->rSize)
		{
			fseek($this->link, $i, SEEK_SET);
			$deleted = fread($this->link, 2);
			if($deleted[0] == '*')
			{
				continue;
			}
			fseek($this->link, $i + $this->fieldPos[$nameID] , SEEK_SET);
			$buffer = fread($this->link, $this->fieldSize[$nameID]);
			if(rtrim(ltrim($buffer, " "), " ") === $fieldValue)
			{
				array_push($ret, ($i - $this->rStart) / $this->rSize);
			}
			
		}
		return $ret;
	}
	public function getField($rID, $fName)
	{
		$fieldID  = $this->getFieldID($fName);
		$pos = $this->rStart + ($rID * $this->rSize) + $this->fieldPos[$fieldID];
		fseek($this->link, $pos, SEEK_SET);
		$buffer = fread($this->link, $this->fieldSize[$fieldID]);
		return rtrim(ltrim($buffer, " "), " ");
	}
}

$test = new dbf("database/bilet.dbf");
$rID = $test->getRecord("IDB", "1251494");
echo $test->getField($rID, "IDP");

?>