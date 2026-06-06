# Daily auto-commit script for CHP repository
$repoPath = "c:\Users\rajee\Downloads\CHP"
$logFile = "$repoPath\daily-commit.log"

# Function to log messages
function Log-Message {
    param([string]$Message)
    $timestamp = Get-Date -Format "yyyy-MM-dd HH:mm:ss"
    $logEntry = "[$timestamp] $Message"
    Write-Host $logEntry
    Add-Content -Path $logFile -Value $logEntry
}

try {
    # Navigate to repo
    Set-Location $repoPath
    Log-Message "Starting daily commit check..."
    
    # Fetch latest changes
    git fetch origin 2>&1 | Out-Null
    Log-Message "Fetched latest from remote"
    
    # Check for changes
    $status = git status --porcelain
    
    if ($status) {
        Log-Message "Changes detected. Committing..."
        
        # Stage all changes
        git add -A
        
        # Create commit message with timestamp
        $commitMessage = "Daily update: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss')"
        
        # Commit changes
        git commit -m $commitMessage
        Log-Message "Committed: $commitMessage"
        
        # Pull latest from remote to avoid conflicts
        git pull origin main --rebase
        
        # Push to remote
        git push origin main
        Log-Message "Pushed changes to remote"
    } else {
        Log-Message "No changes detected. Skipping commit."
    }
    
    Log-Message "Daily commit check completed successfully"
}
catch {
    Log-Message "ERROR: $_"
}
