import matplotlib.pyplot as plt
import os


# Read stats from file
with open('game_stats.txt', 'r') as f:
        data = f.readline().split()
        total_games = int(data[0])
        player_wins = int(data[1])
        dealer_wins = int(data[2])
        ties = int(data[3])
# Create pie chart
labels = ['Player Wins', 'Dealer Wins', 'Ties']
sizes = [player_wins, dealer_wins, ties]
colors = ['#4CAF50', '#F44336', '#FFC107']
explode = (0.1, 0, 0)  # Explode player wins slice

plt.figure(figsize=(10, 6))
plt.pie(sizes, explode=explode, labels=labels, colors=colors,
        autopct='%1.1f%%', shadow=True, startangle=90)
plt.title(f'Blackjack Statistics\nTotal Games: {total_games}', fontsize=16, fontweight='bold')
plt.axis('equal')

# Save the chart
plt.savefig('stats_chart.png', dpi=300, bbox_inches='tight')
print(f"Chart generated successfully!")
print(f"Total Games: {total_games}")
print(f"Player Wins: {player_wins} ({100*player_wins/total_games:.1f}%)")
print(f"Dealer Wins: {dealer_wins} ({100*dealer_wins/total_games:.1f}%)")
print(f"Ties: {ties} ({100*ties/total_games:.1f}%)")